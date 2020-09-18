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

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/time.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
};

class BaseDecoder : public IDecoder{
private:
    const char *TAG = "BaseDecoder";
    AVFormatContext *avFormatContext = NULL;
    AVCodecContext *avCodecContext  = NULL;
    AVCodec *avCodec  = NULL;
    AVPacket *avPacket  = NULL;
    AVFrame *avFrame  = NULL;
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

    int InitFFmpegDecoder(JNIEnv * env);
    void AllocBuffer();
    void StartDecodeThread();
    virtual void Prepare(JNIEnv *env) = 0;
    void DecodeLoop();
    void SyncRender();
    void ObtainTimeStamp();
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

    AVFrame* DecodeFrame();

    virtual void RenderFrame(AVFrame *frame) = 0;
    /**
    * 进入等待
    */
    void Wait(long second = 0);

    /**
     * 恢复解码
     */
    void SendSignal();

    AVCodecContext * GetAVCodecContext(){
        return avCodecContext;
    }

    /**
    * 视频数据编码格式
    * @return
    */
    AVPixelFormat video_pixel_format() {
        return avCodecContext->pix_fmt;
    }

    /**
     * 获取解码时间基
     */
    AVRational time_base() {
        return avFormatContext->streams[mStreamIndex]->time_base;
    }

};


#endif //JNI_NDK_LEARNING_BASEDECODER_H
