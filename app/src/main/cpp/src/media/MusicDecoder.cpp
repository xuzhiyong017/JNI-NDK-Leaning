//
// Created by sky on 20-9-11.
//

#include "MusicDecoder.h"
#include "../decode/AudioDecoder.h"


MusicDecoder::MusicDecoder(JNIEnv *env, jstring path) {
    audioDecoder = new AudioDecoder(env,path);
    audioRender = new AudioRender();
    audioDecoder->SetRender(audioRender);
}

MusicDecoder::~MusicDecoder() {
    LOG_ERROR("MusicDecoder","Release","~MusicDecoder()");
}

void MusicDecoder::start() {
    audioDecoder->start();
}

void MusicDecoder::pause() {
    audioDecoder->pause();
}

void MusicDecoder::stop() {
    audioDecoder->stop();
}
