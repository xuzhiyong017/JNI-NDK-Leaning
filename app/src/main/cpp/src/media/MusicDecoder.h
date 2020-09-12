//
// Created by sky on 20-9-11.
//

#ifndef JNI_NDK_LEARNING_MUSICDECODER_H
#define JNI_NDK_LEARNING_MUSICDECODER_H

#include "../decode/AudioDecoder.h"
#include "../render/AudioRender.h"

class MusicDecoder  {
public:
    MusicDecoder(JNIEnv * env,jstring path);
    ~MusicDecoder();

    void start();
    void pause();
    void stop();

private:
    AudioDecoder *audioDecoder = nullptr;
    AudioRender *audioRender = nullptr;
};


#endif //JNI_NDK_LEARNING_MUSICDECODER_H
