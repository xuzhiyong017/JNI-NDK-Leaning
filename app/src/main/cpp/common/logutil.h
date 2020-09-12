//
// Created by sky on 20-8-15.
//
#include <android/log.h>
#ifndef JNI_NDK_LEARNING_LOGUTIL_H
#define JNI_NDK_LEARNING_LOGUTIL_H

#define LOG

#ifdef LOG
#define LOG_I(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_INFO,TAG,FORMAT,##__VA_ARGS__);
#define LOG_E(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,TAG,FORMAT,##__VA_ARGS__);

#define LOGD(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,TAG,FORMAT,##__VA_ARGS__);
#define LOGI(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_INFO,TAG,FORMAT,##__VA_ARGS__);
#define LOGW(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_WARN,TAG,FORMAT,##__VA_ARGS__);
#define LOGE(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,TAG,FORMAT,##__VA_ARGS__);

#define LOG_INFO(TAG, SPEC, FMT, ...) LOG_I(TAG, "[%s] " FMT, SPEC, ##__VA_ARGS__)
#define LOG_ERROR(TAG, SPEC, FMT, ...) LOG_E(TAG, "[%s] " FMT, SPEC, ##__VA_ARGS__)
#else
#define LOGD(TAG, FORMAT,...);
    #define LOGI(TAG, FORMAT,...);
    #define LOGW(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_WARN,TAG,FORMAT,##__VA_ARGS__);
    #define LOGE(TAG, FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,TAG,FORMAT,##__VA_ARGS__);
#endif


#endif //JNI_NDK_LEARNING_LOGUTIL_H
