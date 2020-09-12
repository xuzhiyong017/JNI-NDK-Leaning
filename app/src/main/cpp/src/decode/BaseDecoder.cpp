//
// Created by sky on 20-9-9.
//

#include "BaseDecoder.h"
#include "../utils/time.c"

BaseDecoder::BaseDecoder(JNIEnv *env, jstring path) {
    mPathRef = env->NewGlobalRef(path);
    mPath = env->GetStringUTFChars(path,NULL);
    env->GetJavaVM(&mJavaVm);
    StartDecodeThread();
}

BaseDecoder::~BaseDecoder() {
    LOG_ERROR(TAG,"BaseDecoder","BaseDecoder ~BaseDecoder()");
    if (avFormatContext != NULL) delete avFormatContext;
    if (avCodecContext != NULL) delete avCodecContext;
    if (avFrame != NULL) delete avFrame;
    if (avPacket != NULL) delete avPacket;
}

void BaseDecoder::StartDecodeThread() {
    std::shared_ptr<BaseDecoder> that(this);
    std::thread t(Decode,that);
    t.detach();
}

void BaseDecoder::Decode(std::shared_ptr<BaseDecoder> that) {
    JNIEnv * env;

    if(that->mJavaVm->AttachCurrentThread(&env,NULL) != JNI_OK){
        LOGE(that->TAG,that->LogSpec(),"Fail to Init decode thread");
        return;
    }

    if(that->InitFFmpegDecoder(env) == 0){
        that->AllocBuffer();
        av_usleep(1000);
        that->Prepare(env);
        that->DecodeLoop();
    }

    that->DecodeFinish(env);

    that->mJavaVm->DetachCurrentThread();
}

int BaseDecoder::InitFFmpegDecoder(JNIEnv *env) {
    avFormatContext = avformat_alloc_context();

    if(avformat_open_input(&avFormatContext,mPath,NULL,NULL) != 0){
        LOG_ERROR(TAG, LogSpec(), "Fail to open file [%s]", mPath);
        DecodeFinish(env);
        return -1;
    }

    if(avformat_find_stream_info(avFormatContext,NULL) < 0){
        LOG_ERROR(TAG,LogSpec(),"Fail to find stream info");
        DecodeFinish(env);
        return -1;
    }

    int index = -1;
    for (int i = 0; i < avFormatContext->nb_streams; ++i) {
        if(avFormatContext->streams[i]->codecpar->codec_type == GetMediaType()){
            index = i;
            break;
        }
    }

    if(index == -1){
        LOG_ERROR(TAG,LogSpec(),"Fail to find stream index");
        DecodeFinish(env);
        return -1;
    }
    mStreamIndex = index;

    AVCodecParameters *codecpar = avFormatContext->streams[index]->codecpar;

    if(avCodec == NULL){
        avCodec = avcodec_find_decoder(codecpar->codec_id);
    }

    avCodecContext = avcodec_alloc_context3(avCodec);
    if(avcodec_parameters_to_context(avCodecContext,codecpar) != 0){
        LOG_ERROR(TAG,LogSpec(),"Fail to obtain av codec context");
        DecodeFinish(env);
        return -1;
    }

    if(avcodec_open2(avCodecContext,avCodec,NULL) < 0){
        LOG_ERROR(TAG,LogSpec(),"Fail to open av codec");
        DecodeFinish(env);
        return -1;
    }

    mDuration = (long)((float)avFormatContext->duration/AV_TIME_BASE * 1000);

    LOG_INFO(TAG,LogSpec(),"Decoder init success");
    return 0;
}

void BaseDecoder::AllocBuffer() {
    avFrame = av_frame_alloc();
    avPacket = av_packet_alloc();
}

void BaseDecoder::DecodeLoop() {
    if(mState == STOP){
        mState = START;
    }
    LOG_INFO(TAG,LogSpec(),"Decode Loop start");
    while(true){
        if(mState != DECODEING
        && mState != START
        && mState != STOP){
            Wait();
            mStartTime = getSystemTime();
        }

        if(mState == STOP){
            LOG_ERROR(TAG,"Release","BaseDecoder stop break while");
            break;
        }

        if(-1 == mStartTime){
            mStartTime = getSystemTime();
        }

        if(DecodeFrame() != NULL){

            if(mState == START){
                mState = PAUSE;
            }
        }else{
            LOGI(TAG,LogSpec(),"mState= %d",mState);
            mState = FINISH;
        }

    }
}

AVFrame * BaseDecoder::DecodeFrame() {
    int ret = av_read_frame(avFormatContext,avPacket);
    while (ret == 0){
        if(avPacket->stream_index == mStreamIndex){
            switch (avcodec_send_packet(avCodecContext,avPacket)){
                case AVERROR_EOF:{
                    av_packet_unref(avPacket);
                    LOG_ERROR(TAG,LogSpec(),"Decoder error: %s",av_err2str(AVERROR_EOF));
                    return NULL;
                }
                case AVERROR(EAGAIN):
                    LOG_ERROR(TAG,LogSpec(),"Decoder error: %s",av_err2str(AVERROR(EAGAIN)));
                    break;
                case AVERROR(EINVAL):
                    LOG_ERROR(TAG,LogSpec(),"Decoder error: %s",av_err2str(AVERROR(EINVAL)));
                    break;
                case AVERROR(ENOMEM):
                    LOG_ERROR(TAG,LogSpec(),"Decoder error: %s",av_err2str(AVERROR(ENOMEM)));
                    break;
                default:
                    break;
            }

            //一个packet包含多个frame
            int frameCount = 0;
            while (avcodec_receive_frame(avCodecContext,avFrame) == 0){
                ObtainTimeStamp();
                RenderFrame(avFrame);
                frameCount++;
            }
            LOG_INFO(TAG,LogSpec(),"Decoder onePacket frameCount: %d",frameCount);
            return avFrame;
        }

        av_packet_unref(avPacket);
        ret = av_read_frame(avFormatContext,avPacket);
    }
    av_packet_unref(avPacket);
    LOG_INFO(TAG,LogSpec(),"ret = %d",ret);
    return NULL;
}

void BaseDecoder::Wait(long second) {
    pthread_mutex_lock(&mMutex);
    if(second > 0){
        timeval now;
        timespec outtime;
        gettimeofday(&now,NULL);
        outtime.tv_sec = now.tv_sec + second;
        outtime.tv_nsec = now.tv_usec * 1000;
        pthread_cond_timedwait(&mCond,&mMutex,&outtime);
    }else{
        pthread_cond_wait(&mCond,&mMutex);
    }
    pthread_mutex_unlock(&mMutex);
}

void BaseDecoder::SendSignal() {
    pthread_mutex_lock(&mMutex);
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mMutex);
}

void BaseDecoder::DecodeFinish(JNIEnv *env) {
    LOG_INFO(TAG,LogSpec(),"Decode finish");
    if(avPacket != NULL){
        av_packet_free(&avPacket);
    }

    if(avFrame != NULL){
        av_frame_free(&avFrame);
    }

    if(avCodecContext != NULL){
        avcodec_close(avCodecContext);
        avcodec_free_context(&avCodecContext);
    }

    if(avFormatContext != NULL){
        avformat_close_input(&avFormatContext);
        avformat_free_context(avFormatContext);
    }

    if(mPathRef != NULL && mPath != NULL){
        env->ReleaseStringUTFChars(static_cast<jstring>(mPathRef), mPath);
        env->DeleteGlobalRef(mPathRef);
        mPathRef = NULL;
        mPath = NULL;
    }
    Release();
}

void BaseDecoder::start() {
    mState = DECODEING;
    SendSignal();
}

void BaseDecoder::stop() {
    mState = STOP;
    SendSignal();
}

void BaseDecoder::pause() {
    mState = PAUSE;
    SendSignal();
}

bool BaseDecoder::IsRunning(){
    return DECODEING == mState;
}

long BaseDecoder::getDuration() {
    return mDuration;
}

long BaseDecoder::getCurPos() {
    return mStartTime;
}

void BaseDecoder::ObtainTimeStamp() {
    if(avFrame->pkt_dts != AV_NOPTS_VALUE) {
        mCurTime = avPacket->dts;
    } else if (avFrame->pts != AV_NOPTS_VALUE) {
        mCurTime = avFrame->pts;
    } else {
        mCurTime = 0;
    }
    mCurTime = (int64_t)((mCurTime * av_q2d(avFormatContext->streams[mStreamIndex]->time_base)) * 1000);
}
