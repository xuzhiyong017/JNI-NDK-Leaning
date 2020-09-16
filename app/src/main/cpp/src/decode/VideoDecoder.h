//
// Created by sky on 20-9-16.
//

#ifndef JNI_NDK_LEARNING_VIDEODECODER_H
#define JNI_NDK_LEARNING_VIDEODECODER_H


#include "BaseDecoder.h"
#include "../render/IVideoRender.h"

class VideoDecoder : public BaseDecoder {
private:
    int totalCountFrame = 0;
    IVideoRender *iRender = NULL;
    SwrContext *mSwrContext = NULL;
    //视频数据目标格式
    int showWidth;
    int showHeight;
    const AVPixelFormat DST_FORMAT = AV_PIX_FMT_RGBA;

    void initRender(JNIEnv *env);
    void initSwrAndBuffer();
public:
    VideoDecoder(JNIEnv *env, const jstring path);
    ~VideoDecoder();

    void SetRender(IVideoRender *render);

protected:
    void Prepare(JNIEnv *env) override ;

    void Release() override;

    void RenderFrame(AVFrame *frame) override;

    const char *const LogSpec() override;

    AVMediaType GetMediaType() override;

};


#endif //JNI_NDK_LEARNING_VIDEODECODER_H
