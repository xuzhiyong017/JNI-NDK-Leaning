//
// Created by sky on 20-9-16.
//

#include "VideoDecoder.h"

static const char * TAG_ = "VideoDecoder";

VideoDecoder::VideoDecoder(JNIEnv *env, const jstring path) :BaseDecoder(env,path) {

}

VideoDecoder::~VideoDecoder() {
    LOG_ERROR(TAG_,"Release","VideoDecoder::~VideoDecoder()");
    if(iRender != NULL){
        delete iRender;
    }
}

void VideoDecoder::SetRender(IVideoRender *render) {
    this->iRender = render;
}

void VideoDecoder::Prepare(JNIEnv *env) {
    initRender(env);
    initSwrAndBuffer();
}

void VideoDecoder::Release() {
    if(iRender){
        iRender->ReleaseRender();
    }
}

void VideoDecoder::RenderFrame(AVFrame *frame) {

}

const char *const VideoDecoder::LogSpec() {
    return "VideoDecoder";
}

AVMediaType VideoDecoder::GetMediaType() {
    return AVMEDIA_TYPE_VIDEO;
}

void VideoDecoder::initRender(JNIEnv *env) {
    if(iRender){
        int dstSize[2] = {-1,-1};
        iRender->initRender(env,width(),height(),dstSize);

        showWidth = dstSize[0];
        showHeight = dstSize[1];
        if(showWidth == -1){
            showWidth = width();
        }
        if(showHeight == -1){
            showHeight = height();
        }
    }
}

void VideoDecoder::initSwrAndBuffer() {

}
