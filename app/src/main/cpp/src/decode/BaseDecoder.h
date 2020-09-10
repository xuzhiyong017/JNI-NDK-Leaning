//
// Created by sky on 20-9-9.
//

#ifndef JNI_NDK_LEARNING_BASEDECODER_H
#define JNI_NDK_LEARNING_BASEDECODER_H


#include <jni.h>
#include <pthread.h>
#include <memory>
#include <thread>
#include "IDecoder.h"
#include "DecodeState.h"
#include <logutil.h>
#include "../utils/time.c"

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/time.h>
};

class BaseDecoder : public IDecoder{
private:
    const char *TAG = "BaseDecoder";
    AVFormatContext *avFormatContext;
    AVCodecContext *avCodecContext;
    AVCodec *avCodec;
    AVPacket *avPacket;
    AVFrame *avFrame;
    int64_t mCurTime = 0;
    long mDuration = 0;
    int64_t mStartTime = -1;
    int mStreamIndex = -1;
    DecodeState mState = STOP;

    JavaVM *mJavaVm = NULL;
    // 原始路径jstring引用，否则无法在线程中操作
    jobject mPathRef = NULL;
    const char *mPath = NULL;

    pthread_mutex_t mMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t mCond = PTHREAD_COND_INITIALIZER;

    void Init(JNIEnv *env,char * path);
    void InitFFmpegDecoder(JNIEnv * env);
    void AllocBuffer();
    void StartDecodeThread();
    virtual void Prepare(JNIEnv *env) = 0;
    void DecodeLoop();
    void GetTimeStamp();
    void DecodeFinish(JNIEnv * env);
    static void Decode(std::shared_ptr<BaseDecoder> that);

public:
    BaseDecoder(JNIEnv * env,jstring path);
    virtual ~BaseDecoder();
    int width(){
        return avCodecContext->width;
    }

    int height(){
        return avCodecContext->height;
    }

    long duration(){
        return mDuration;
    }

    void start() override;
    void pause() override ;
    void stop() override;
    bool IsRunning() override;
    long getDuration() override;
    long getCurPos() override;

protected:
    const char * path() {
        return mPath;
    }

    /**
    * Log前缀
    */
    virtual const char *const LogSpec() = 0;

    virtual AVMediaType GetMediaType() = 0;

    virtual void Release() = 0;

    /**
    * 进入等待
    */
    void Wait(long second = 0);

    /**
     * 恢复解码
     */
    void SendSignal();
};


#endif //JNI_NDK_LEARNING_BASEDECODER_H
