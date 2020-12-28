#include <jni.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "common/logutil.h"
#include "BitmapUtils.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jni_1ndk_1learning_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1ndk_1learning_MainActivity_changeName(JNIEnv *env, jobject thiz) {
    jclass j_clz = env->FindClass("com/example/jni_ndk_learning/MainActivity");
    jfieldID  j_field = env->GetFieldID(j_clz,"name","Ljava/lang/String;");
    jstring value = env->NewStringUTF("张德威");
    env->SetObjectField(thiz,j_field,value);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jni_1ndk_1learning_MainActivity_changeName1(JNIEnv *env, jclass thiz,jobject bitmap) {
    __android_log_print(ANDROID_LOG_ERROR,"TAG","+%p",bitmap);
    BitmapUtils::mat2Bitmap(env,bitmap);
}