//
// Created by sky on 20-9-10.
//

#include "AudioDecoder.h"

static const char * TAG_ = "AudioDecoder";

AudioDecoder::AudioDecoder(JNIEnv *env, const jstring path):BaseDecoder(env,path) {

}

AudioDecoder::~AudioDecoder(){
    LOG_ERROR(TAG_,"Release","AudioDecoder::~AudioDecoder()");
    if(iRender != NULL){
        delete iRender;
    }
}

void AudioDecoder::SetRender(IRender *render) {
    this->iRender = render;
}

void AudioDecoder::Prepare(JNIEnv *env) {
    InitSwrAndOutBuffer();
    iRender->InitRender();
}

void AudioDecoder::Release() {
    iRender->Release();
    LOG_ERROR(TAG_,"Release","AudioDecoder inner Release");
}

void AudioDecoder::RenderFrame(AVFrame *frame) {
    int ret = swr_convert(mSwrContext,&m_AudioOutBuffer,m_DstFrameDataSze / 2,(const uint8_t**)frame->data,frame->nb_samples);
    if(ret > 0){
        totalCountFrame++;
        iRender->Render(m_AudioOutBuffer,m_DstFrameDataSze);
    }

}

const char *const AudioDecoder::LogSpec() {
    return "AudioDecoder";
}

AVMediaType AudioDecoder::GetMediaType() {
    return AVMEDIA_TYPE_AUDIO;
}

void AudioDecoder::InitSwrAndOutBuffer() {
    AVCodecContext * codeCtx = GetAVCodecContext();

    mSwrContext = swr_alloc_set_opts(mSwrContext,
                                     AUDIO_DST_CHANNEL_LAYOUT,
                                     DST_SAMPLT_FORMAT,
                                     AUDIO_DST_SAMPLE_RATE,
                                     codeCtx->channel_layout,
                                     codeCtx->sample_fmt,
                                     codeCtx->sample_rate,
                                     0,
                                     NULL);


    swr_init(mSwrContext);

    int src_nb_channels = av_get_channel_layout_nb_channels(codeCtx->channel_layout);

    LOGI(TAG_,"AudioDecoder::InitSwrAndOutBuffer audio metadata sample rate: %d, channel: %d, format: %d, frame_size: %d, layout: %lld",
            codeCtx->sample_rate, codeCtx->channels, codeCtx->sample_fmt, codeCtx->frame_size,codeCtx->channel_layout);

    m_nbSamples = (int)av_rescale_rnd(codeCtx->frame_size,AUDIO_DST_SAMPLE_RATE,codeCtx->sample_rate,AV_ROUND_UP);
    m_DstFrameDataSze = av_samples_get_buffer_size(NULL,AUDIO_DST_CHANNEL_COUNTS,m_nbSamples,DST_SAMPLT_FORMAT,1);
    LOGI(TAG_,"AudioDecoder::InitSwrAndOutBuffer [m_nbSamples, m_DstFrameDataSze]=[%d, %d]", m_nbSamples, m_DstFrameDataSze);

    m_AudioOutBuffer = (uint8_t *) malloc(m_DstFrameDataSze);
}
