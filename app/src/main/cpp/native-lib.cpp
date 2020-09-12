#include <jni.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "common/logutil.h"
#include "src/media/MusicDecoder.h"

extern "C" {
    #include <libavcodec/version.h>
    #include <libavcodec/avcodec.h>
    #include <libavformat/version.h>
    #include <libavutil/version.h>
    #include <libavfilter/version.h>
    #include <libswresample/version.h>
    #include <libswscale/version.h>


    JNIEXPORT jstring JNICALL
    Java_com_example_jni_1ndk_1learning_MainActivity_stringFromJNI(
            JNIEnv *env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT jstring JNICALL
    Java_com_example_jni_1ndk_1learning_MainActivity_getFFmpegInfo(JNIEnv *env, jobject thiz) {
        char strBuffer[1024 * 4] = {0};
        strcat(strBuffer, "libavcodec : ");
        strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
        strcat(strBuffer, "\nlibavformat : ");
        strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
        strcat(strBuffer, "\nlibavutil : ");
        strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
        strcat(strBuffer, "\nlibavfilter : ");
        strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
        strcat(strBuffer, "\nlibswresample : ");
        strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
        strcat(strBuffer, "\nlibswscale : ");
        strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
        strcat(strBuffer, "\navcodec_configure : \n");
        strcat(strBuffer, avcodec_configuration());
        strcat(strBuffer, "\navcodec_license : ");
        strcat(strBuffer, avcodec_license());
        LOGI("native-lib","GetFFmpegVersion\n%s", strBuffer);
        return env->NewStringUTF(strBuffer);
    }

    static MusicDecoder *musicDecoder;
    const char * const TAG = "native-lib-input";

    JNIEXPORT void JNICALL
    Java_com_example_jni_1ndk_1learning_decode_NativeMusicDecoder_createMusicDecoder(JNIEnv *env,
                                                                                     jobject thiz,
                                                                                     jstring path) {
        musicDecoder = new MusicDecoder(env,path);
        LOGI(TAG,"MusicDecoder create %d",1);
    }

    JNIEXPORT void JNICALL
    Java_com_example_jni_1ndk_1learning_decode_NativeMusicDecoder_start(JNIEnv *env, jobject thiz) {
        if(musicDecoder){
            musicDecoder->start();
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_jni_1ndk_1learning_decode_NativeMusicDecoder_pause(JNIEnv *env, jobject thiz) {
        if(musicDecoder){
            musicDecoder->pause();
        }
    }

    JNIEXPORT void JNICALL
    Java_com_example_jni_1ndk_1learning_decode_NativeMusicDecoder_release(JNIEnv *env, jobject thiz) {
        if(musicDecoder){
            musicDecoder->stop();
            delete musicDecoder;
            musicDecoder = nullptr;
        }
    }
};

