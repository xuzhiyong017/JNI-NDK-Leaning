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
    if(audioDecoder){
        LOG_ERROR("AudioDecder","Release","MusicDecoder holder Audio ~ start");
        audioDecoder->stop();
        LOG_ERROR("AudioDecder","Release","MusicDecoder holder Audio ~ end");
        delete audioDecoder;
        LOG_ERROR("AudioDecder","Release","MusicDecoder holder Audio ~ delete");
    }
}

void MusicDecoder::start() {
    audioDecoder->start();
}

void MusicDecoder::pause() {
    audioDecoder->pause();
}

void MusicDecoder::stop() {
    if(audioDecoder){
        LOG_ERROR("AudioDecder","Release","MusicDecoder holder Audio stop start");
        audioDecoder->stop();
        LOG_ERROR("AudioDecder","Release","MusicDecoder holder Audio stop end");
        delete audioDecoder;
        audioDecoder = nullptr;
        LOG_ERROR("AudioDecder","Release","MusicDecoder holder Audio stop delete");
    }

    if(audioRender){
        delete audioRender;
        audioRender = nullptr;
    }
}
