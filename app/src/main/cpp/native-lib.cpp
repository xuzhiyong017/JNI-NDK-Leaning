#include <jni.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "common/logutil.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jni_1ndk_1learning_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
