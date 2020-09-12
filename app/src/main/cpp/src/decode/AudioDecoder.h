//
// Created by sky on 20-9-10.
//

#ifndef JNI_NDK_LEARNING_AUDIODECODER_H
#define JNI_NDK_LEARNING_AUDIODECODER_H

#include "BaseDecoder.h"
#include "../render/IRender.h"

// 音频编码采样率
static const int AUDIO_DST_SAMPLE_RATE = 44100;
// 音频编码通道数
static const int AUDIO_DST_CHANNEL_COUNTS = 2;
// 音频编码声道格式
static const uint64_t AUDIO_DST_CHANNEL_LAYOUT = AV_CH_LAYOUT_STEREO;
// 音频编码比特率
static const int AUDIO_DST_BIT_RATE = 64000;
// ACC音频一帧采样数
static const int ACC_NB_SAMPLES = 1024;

class AudioDecoder : public BaseDecoder {
private:
    int totalCountFrame = 0;
    IRender *iRender;
    SwrContext *mSwrContext = NULL;
    uint8_t  *m_AudioOutBuffer = nullptr;
    int  m_nbSamples = 1024;
    int  m_DstFrameDataSze = 0;
    const AVSampleFormat DST_SAMPLT_FORMAT = AV_SAMPLE_FMT_S16;
    void InitSwrAndOutBuffer();
public:
    AudioDecoder(JNIEnv *env, const jstring path);
    ~AudioDecoder();

    void SetRender(IRender *render);


protected:
    void Prepare(JNIEnv *env) override ;

    void Release() override;

    void RenderFrame(AVFrame *frame) override;

    const char *const LogSpec() override;

    AVMediaType GetMediaType() override;

};


#endif //JNI_NDK_LEARNING_AUDIODECODER_H
