//
// Created by sky on 20-9-9.
//

#include <thread>
#include <libavutil/time.h>
#include "BaseDecoder.h"


BaseDecoder::BaseDecoder(JNIEnv *env, jstring path) {
    mPathRef = env->NewGlobalRef(path);
    mPath = env->GetStringUTFChars(path,NULL);
    env->GetJavaVM(&mJavaVm);
}

BaseDecoder::~BaseDecoder() {
    if(avFormatContext) delete avFormatContext;
    if(avCodecContext) delete avCodecContext;
    if(avFrame) delete avFrame;
    if(avPacket) delete avPacket;
}

void BaseDecoder::StartDecodeThread() {
    std::shared_ptr<BaseDecoder> that(this);
    std::thread t(Decode,that);
    t.detach();
}

void BaseDecoder::Decode(std::shared_ptr<BaseDecoder> that) {
    JNIEnv * env;

    if(that->mJavaVm->AttachCurrentThread(&env,NULL) != JNI_OK){
        LOGE(that->TAG,that->LogSpec(),"Fail to Init decode thread");
        return;
    }

    that->InitFFmpegDecoder(env);
    that->AllocBuffer();
    av_usleep(1000)
    that->Prepare(env);
    that->DecodeLoop();
    that->DecodeFinish(env);

    that->mJavaVm->DetachCurrentThread();
}

void BaseDecoder::InitFFmpegDecoder(JNIEnv *env) {
    avFormatContext = avformat_alloc_context();

    if(avformat_open_input(&avFormatContext,mPath,NULL,NULL) != 0){
        LOGE(TAG,LogSpec(),"Fail to open file [%s]", mPath);
        DecodeFinish(env);
        return;
    }

    if(avformat_find_stream_info(avFormatContext.NULL) < 0){
        LOGE(TAG,LogSpec(),"Fail to find stream info");
        DecodeFinish(env);
    }

    int index = -1;
    for (int i = 0; i < avFormatContext->nb_streams; ++i) {
        if(avFormatContext->streams[i]->codecpar->codec_type == GetMediaType()){
            index = i;
            break;
        }
    }

    if(index == -1){
        LOGE(TAG,LogSpec(),"Fail to find stream index");
        DecodeFinish(env);
    }
    mStreamIndex = index;

    AVCodecParameters *codecpar = avFormatContext->streams[index]->codecpar;

    if(avCodec == NULL){
        avCodec = avcodec_find_decoder(codecpar->codec_id);
    }

    avCodecContext = avcodec_alloc_context3(avCodec);
    if(avcodec_parameters_to_context(avCodecContext,codecpar) != 0){
        LOGE(TAG,LogSpec(),"Fail to obtain av codec context");
        DecodeFinish(env);
        return;
    }

    if(avcodec_open2(avCodecContext,avCodec,NULL) < 0){
        LOGE(TAG,LogSpec(),"Fail to open av codec");
        DecodeFinish(env);
        return;
    }

    mDuration = (long)((float)avFormatContext->duration/AV_TIME_BASE * 1000);

    LOGI(TAG,LogSpec(),"Decoder init success");
}

void BaseDecoder::AllocBuffer() {
    avFrame = av_frame_alloc();
    avPacket = av_packet_alloc();
}

void BaseDecoder::DecodeLoop() {

}