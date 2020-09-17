//
// Created by sky on 20-9-16.
//

#include "NativePlayer.h"

NativePlayer::NativePlayer(JNIEnv *env, jstring path, jobject surface) {
    videoDecoder = new VideoDecoder(env,path);
    videoRender = new VideoRender(env,surface);
    videoDecoder->SetRender(videoRender);

    audioDecoder = new AudioDecoder(env,path);
    audioRender = new AudioRender();
    audioDecoder->SetRender(audioRender);
}

NativePlayer::~NativePlayer() {

}

void NativePlayer::start() {
    if(videoDecoder){
        videoDecoder->start();
    }

    if(audioDecoder){
        audioDecoder->start();
    }
}

void NativePlayer::pause() {
    if(videoDecoder){
        videoDecoder->pause();
    }

    if(audioDecoder){
        audioDecoder->pause();
    }
}

void NativePlayer::release() {
    if(videoDecoder){
        videoDecoder->stop();
    }

    if(audioDecoder){
        audioDecoder->stop();
    }
}
