//
// Created by sky on 20-9-16.
//

#ifndef JNI_NDK_LEARNING_NATIVEPLAYER_H
#define JNI_NDK_LEARNING_NATIVEPLAYER_H

#include <jni.h>
#include "../decode/VideoDecoder.h"
#include "../decode/AudioDecoder.h"
#include "../render/AudioRender.h"
#include "../render/VideoRender.h"

class NativePlayer {
public:
    NativePlayer(JNIEnv * env,jstring path,jobject surface);
    ~NativePlayer();

    void start();
    void pause();
    void release();
private:
    VideoDecoder * videoDecoder = NULL;
    AudioDecoder * audioDecoder = NULL;
    AudioRender * audioRender = NULL;
    VideoRender * videoRender = NULL;
};


#endif //JNI_NDK_LEARNING_NATIVEPLAYER_H
