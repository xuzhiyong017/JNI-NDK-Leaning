//
// Created by sky on 20-9-9.
//

#ifndef JNI_NDK_LEARNING_IDECODER_H
#define JNI_NDK_LEARNING_IDECODER_H

class IDecoder{
public:
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual bool IsRunning() = 0;
    virtual long getDuration() = 0;
    virtual long getCurPos() = 0;
};

#endif //JNI_NDK_LEARNING_IDECODER_H
