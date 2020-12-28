//
// Created by sky on 20-12-24.
//

#ifndef JNI_NDK_LEARNING_BITMAPUTILS_H
#define JNI_NDK_LEARNING_BITMAPUTILS_H

#include <jni.h>

class BitmapUtils {
   public:
        static int mat2Bitmap(JNIEnv * env, jobject bitmap);
};



#endif //JNI_NDK_LEARNING_BITMAPUTILS_H
