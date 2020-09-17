//
// Created by sky on 20-9-16.
//

#include "VideoDecoder.h"
static const char * TAG_ = "VideoDecoder";

VideoDecoder::VideoDecoder(JNIEnv *env, const jstring path) :BaseDecoder(env,path) {

}

VideoDecoder::~VideoDecoder() {
    delete iRender;
}

void VideoDecoder::SetRender(IVideoRender *render) {
    this->iRender = render;
}

void VideoDecoder::Prepare(JNIEnv *env) {
    initRender(env);
    initSwrAndBuffer();
}

void VideoDecoder::Release() {

    if(mAvFrame){
        av_frame_free(&mAvFrame);
        mAvFrame = NULL;
    }

    if(m_buf_for_rgb_frame){
        free(m_buf_for_rgb_frame);
        m_buf_for_rgb_frame = NULL;
    }

    if(mSwsContext){
        sws_freeContext(mSwsContext);
        mSwsContext = NULL;
    }

    if(iRender){
        iRender->ReleaseRender();
        iRender = NULL;
    }
}

void VideoDecoder::RenderFrame(AVFrame *frame) {
    sws_scale(mSwsContext,frame->data,frame->linesize,0,height(),
            mAvFrame->data,mAvFrame->linesize);
    RenderVideoFrame *renderVideoFrame = new RenderVideoFrame(mAvFrame->data[0],mAvFrame->linesize[0],frame->pts,time_base(),NULL,
                                                              false);
    if(iRender){
        iRender->Render(renderVideoFrame);
    }
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

        LOGI(TAG_,LogSpec(), "dst %d, %d", showWidth, showHeight)
    }
    LOGE(TAG_,LogSpec(), "Init render error, you should call SetRender first!")
}

void VideoDecoder::initSwrAndBuffer() {
    mAvFrame = av_frame_alloc();
    int numBytes = av_image_get_buffer_size(DST_FORMAT,showWidth,showHeight,1);
    m_buf_for_rgb_frame = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(mAvFrame->data,mAvFrame->linesize,m_buf_for_rgb_frame,DST_FORMAT,showWidth,showHeight,1);

    mSwsContext = sws_getContext(width(),height(),video_pixel_format(),
                showWidth,showHeight,DST_FORMAT,
                SWS_FAST_BILINEAR,NULL,NULL,NULL);
}
