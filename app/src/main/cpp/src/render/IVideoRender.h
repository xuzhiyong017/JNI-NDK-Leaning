//
// Created by sky on 20-9-16.
//

#ifndef JNI_NDK_LEARNING_IVIDEORENDER_H
#define JNI_NDK_LEARNING_IVIDEORENDER_H

#include <stdint.h>
#include <jni.h>
#include "RenderVideoFrame.h"

class IVideoRender {
public:
    virtual void initRender(JNIEnv * env,int videoWidth,int videoHeight,int *dstSize) = 0;
    virtual void Render(RenderVideoFrame *frame);
    virtual void ReleaseRender();
    virtual ~IVideoRender();
};


#endif //JNI_NDK_LEARNING_IVIDEORENDER_H
