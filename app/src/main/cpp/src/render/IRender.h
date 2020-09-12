//
// Created by sky on 20-9-11.
//

#ifndef JNI_NDK_LEARNING_IRENDER_H
#define JNI_NDK_LEARNING_IRENDER_H

#include <cstdint>

class IRender{
public:
    virtual void InitRender() = 0;
    virtual void Release() = 0;
    virtual void Render(uint8_t *pcm, int size) = 0;
    virtual ~IRender(){}

};

#endif //JNI_NDK_LEARNING_IRENDER_H
