//
// Created by sky on 20-9-11.
//

#include <logutil.h>
#include <unistd.h>
#include "AudioRender.h"

static const char *TAG = "AudioRender";

AudioRender::AudioRender() {

}

AudioRender::~AudioRender() {
    LOG_ERROR("AudioRender","Release","~AudioRender()");
}

bool AudioRender::createEngine() {
    SLresult  lresult = slCreateEngine(&mSLObj,0,NULL,0,NULL,NULL);
    if(checkError(lresult,"engine")) return false;

    lresult = (*mSLObj)->Realize(mSLObj,SL_BOOLEAN_FALSE);
    if(checkError(lresult,"engine realize")) return false;

    lresult = (*mSLObj)->GetInterface(mSLObj,SL_IID_ENGINE,&mEngine);
    return !checkError(lresult,"engine Interface");
}

bool AudioRender::createMixer() {
    const SLInterfaceID  mids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean mreq[1] = {SL_BOOLEAN_FALSE};
    SLresult lresult = (*mEngine)->CreateOutputMix(mEngine,&mMixObj,1,mids,mreq);
    if (checkError(lresult, "Output Mix")) return false;

    lresult = (*mMixObj)->Realize(mMixObj,SL_BOOLEAN_FALSE);
    if (checkError(lresult, "Output Mix Realize")) return false;

    lresult = (*mMixObj)->GetInterface(mMixObj,SL_IID_ENVIRONMENTALREVERB,&mMixEvnReverb);
    if (checkError(lresult, "Output Mix Env Reverb")) return false;

    if(lresult == SL_RESULT_SUCCESS){
        (*mMixEvnReverb)->SetEnvironmentalReverbProperties(mMixEvnReverb,&mMixEvnSetting);
    }

    return true;
}

bool AudioRender::configPlayer() {
    SLDataLocator_AndroidSimpleBufferQueue androidSimpleBufferQueue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,SL_QUEUE_BUFFER_COUNT};
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            (SLint32)2,
            SL_SAMPLINGRATE_44_1,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN
    };

    SLDataSource slDataSource = {&androidSimpleBufferQueue,&pcm};

    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX,mMixObj};
    SLDataSink slDataSink = {&outputMix,NULL};

    const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE,SL_IID_EFFECTSEND,SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE,SL_BOOLEAN_TRUE,SL_BOOLEAN_TRUE};

    SLresult lresult = (*mEngine)->CreateAudioPlayer(mEngine,&mPlayerObj,&slDataSource,&slDataSink,3,ids,req);
    if(checkError(lresult,"Player"))return false;

    lresult = (*mPlayerObj)->Realize(mPlayerObj,SL_BOOLEAN_FALSE);
    if(checkError(lresult,"Player Realize")) return false;

    lresult = (*mPlayerObj)->GetInterface(mPlayerObj,SL_IID_PLAY,&mPlayer);
    if(checkError(lresult,"Player interface")) return false;

    lresult = (*mPlayerObj)->GetInterface(mPlayerObj,SL_IID_BUFFERQUEUE,&mPCMBuffer);
    if(checkError(lresult,"Player Queue Buffer")) return false;

    lresult = (*mPlayerObj)->GetInterface(mPlayerObj,SL_IID_VOLUME,&mSlVolumeItf);
    if(checkError(lresult,"Player Volume Interface")) return false;

    lresult = (*mPCMBuffer)->RegisterCallback(mPCMBuffer,sReadPcmBufferCbFun,this);
    if(checkError(lresult,"Register Callback Interface")) return false;

    LOGI(TAG,"AudioRender init success");
    return true;
}

void AudioRender::startRender() {
    while (mQueue.empty()){
        WaitForCache();
    }

    (*mPlayer)->SetPlayState(mPlayer,SL_PLAYSTATE_PLAYING);
    sReadPcmBufferCbFun(mPCMBuffer,this);
    LOGI(TAG,"AudioRender render start playing");
}

void AudioRender::BlockQueue() {
    if(mPlayer == NULL) return;

    while (!mQueue.empty()){
        AudioPacket *packet = mQueue.front();
        if(packet->used){
            mQueue.pop();
            delete packet;
        }else{
            break;
        }
    }

    LOGD(TAG,"BlockEnqueue thread %d enter",std::this_thread::get_id());

    while (mQueue.empty() && mPlayer != NULL){
        LOGD(TAG,"BlockEnqueue thread %d wait",std::this_thread::get_id());
        WaitForCache();
    }

    LOGD(TAG,"BlockEnqueue thread %d front",std::this_thread::get_id());

    AudioPacket * audioPacket = mQueue.front();
    if(NULL != audioPacket && mPlayer){
        SLresult lresult = (*mPCMBuffer)->Enqueue(mPCMBuffer,audioPacket->pcm,audioPacket->size);
        if(lresult == SL_RESULT_SUCCESS){
            audioPacket->used = true;
        }
    }
}

bool AudioRender::checkError(SLresult result, std::string hint) {
    if(SL_RESULT_SUCCESS != result){
        LOG_ERROR(TAG,"","AudioRender [%s] init fail",hint.c_str());
        return true;
    }
    return false;
}

void AudioRender::sRenderPcm(AudioRender *that) {
    that->startRender();
}

void AudioRender::sReadPcmBufferCbFun(SLAndroidSimpleBufferQueueItf bufferQueueItf, void *context) {
    AudioRender *render = (AudioRender *)context;
    render->BlockQueue();
}



void AudioRender::InitRender() {
    if(!createEngine()) return;
    if(!createMixer()) return;
    if(!configPlayer()) return;
    std::thread t(sRenderPcm,this);
    t.detach();
}

void AudioRender::Release() {
    if(mPlayer){
        (*mPlayer)->SetPlayState(mPlayer,SL_PLAYSTATE_STOPPED);
        mPlayer = NULL;
    }

    NotifyCacheReadySignal();

    if(mPlayerObj){
        (*mPlayerObj)->Destroy(mPlayerObj);
        mPlayerObj = NULL;
        mPCMBuffer = NULL;
    }

    if(mMixObj){
        (*mMixObj)->Destroy(mMixObj);
        mMixObj = NULL;
    }

    if(mSLObj){
        (*mSLObj)->Destroy(mSLObj);
        mSLObj = NULL;
        mEngine = NULL;
    }

    for (int i = 0; i < mQueue.size(); ++i) {
        AudioPacket *packet = mQueue.front();
        if(packet != NULL){
            mQueue.pop();
            delete packet;
        }
    }

}

void AudioRender::Render(uint8_t *pcm, int size) {
    if(mPlayer){
        if(pcm != NULL && size > 0){
            while (mQueue.size() >= 2){
                NotifyCacheReadySignal();
                usleep(20000);
            }
            LOG_INFO(TAG,"","Render thread %d",std::this_thread::get_id());
            uint8_t *data = (uint8_t *) malloc(size);
            memcpy(data,pcm,size);
            AudioPacket *packet = new AudioPacket(data,size);
            mQueue.push(packet);

            NotifyCacheReadySignal();
        }
    }else{
        LOG_INFO(TAG,"","Render thread free pcm");
        free(pcm);
    }
}
