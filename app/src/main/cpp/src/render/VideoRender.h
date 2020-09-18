//
// Created by sky on 20-9-16.
//

#ifndef JNI_NDK_LEARNING_VIDEORENDER_H
#define JNI_NDK_LEARNING_VIDEORENDER_H


#include "IVideoRender.h"
#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C" {
#include <libavutil/mem.h>
};

class VideoRender : public IVideoRender {
private:
    const char *TAG = "VideoRender";

    jobject mSurfaceRef = NULL;
    ANativeWindow_Buffer mOutBuffer;
    ANativeWindow *mWindow = NULL;

    int dstW;
    int dstH;
    int offset;//居中的偏移量
public:
    VideoRender(JNIEnv *env,jobject suface);
    ~VideoRender();

private:
    void initRender(JNIEnv *env, int videoWidth, int videoHeight, int *dstSize) override;

    void Render(RenderVideoFrame *frame) override;

    void ReleaseRender() override;
};


#endif //JNI_NDK_LEARNING_VIDEORENDER_H
