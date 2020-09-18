//
// Created by sky on 20-9-16.
//

#include "VideoRender.h"

VideoRender::VideoRender(JNIEnv *env, jobject suface) {
    mSurfaceRef = env->NewGlobalRef(suface);
}
VideoRender::~VideoRender() {

}


void VideoRender::initRender(JNIEnv *env, int videoWidth, int videoHeight, int *dstSize) {
    mWindow = ANativeWindow_fromSurface(env,mSurfaceRef);

    // 绘制区域的宽高
    int windowWidth = ANativeWindow_getWidth(mWindow);
    int windowHeight = ANativeWindow_getHeight(mWindow);

    dstW = windowWidth;
    dstH = dstW * videoHeight / videoWidth;
    if(dstH > windowHeight){
        dstH = windowHeight;
        dstW = windowHeight * videoWidth / videoHeight;
    }else{
        offset = (windowHeight - dstH) / 2 ;
    }

    ANativeWindow_setBuffersGeometry(mWindow,windowWidth,windowHeight,WINDOW_FORMAT_RGBA_8888);
    dstSize[0] = dstW;
    dstSize[1] = dstH;
}

void VideoRender::Render(RenderVideoFrame *frame) {
    ANativeWindow_lock(mWindow,&mOutBuffer,NULL);
    uint8_t * dst = (uint8_t *) mOutBuffer.bits;

    int dstStride = mOutBuffer.stride * 4;
    int srcStride = frame->line_size;

    for (int i = 0; i < dstH; ++i) {
        memcpy(dst+(offset+i)*dstStride,frame->data + i*srcStride,srcStride);
    }
    ANativeWindow_unlockAndPost(mWindow);
}

void VideoRender::ReleaseRender() {
    if(mWindow != NULL){
        ANativeWindow_release(mWindow);
    }
    av_free(&mOutBuffer);
}


