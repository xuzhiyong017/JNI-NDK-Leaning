//
// Created by sky on 20-9-11.
//

#ifndef JNI_NDK_LEARNING_AUDIORENDER_H
#define JNI_NDK_LEARNING_AUDIORENDER_H


#include <cstdlib>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <memory>
#include <pthread.h>
#include <thread>
#include <queue>

#include "IRender.h"

class AudioRender : public IRender{
private:
    class AudioPacket{
    public:
        AudioPacket(uint8_t * pcm,int size):pcm(pcm),size(size){
        }
        ~AudioPacket(){
            if(pcm != NULL){
                free(pcm);
                pcm = NULL;
                used = false;
            }
        }
        uint8_t * pcm = NULL;
        int size = 0;
        bool used = false;
    };

    const SLuint32 SL_QUEUE_BUFFER_COUNT = 2;

    SLObjectItf mSLObj = NULL;
    SLEngineItf mEngine = NULL;

    SLObjectItf mMixObj = NULL;
    SLEnvironmentalReverbItf  mMixEvnReverb = NULL;
    SLEnvironmentalReverbSettings mMixEvnSetting = SL_I3DL2_ENVIRONMENT_PRESET_DEFAULT;

    SLObjectItf mPlayerObj = NULL;
    SLPlayItf  mPlayer = NULL;
    SLVolumeItf mSlVolumeItf = NULL;

    SLAndroidSimpleBufferQueueItf mPCMBuffer;

    std::queue<AudioPacket *> mQueue;

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    bool createEngine();
    bool createMixer();
    bool configPlayer();
    void startRender();
    void BlockQueue();

    bool checkError(SLresult result,std::string hint);

    void static sRenderPcm(AudioRender *that);
    void static sReadPcmBufferCbFun(SLAndroidSimpleBufferQueueItf bufferQueueItf,void *context);


    void WaitForCache(){
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond,&mutex);
        pthread_mutex_unlock(&mutex);
    }

    void NotifyCacheReadySignal(){
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

public:
    AudioRender();
    ~AudioRender();

    void InitRender() override ;
    void Release() override ;
    void Render(uint8_t *pcm, int size) override;
};


#endif //JNI_NDK_LEARNING_AUDIORENDER_H
