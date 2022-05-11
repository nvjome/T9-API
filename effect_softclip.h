/*
    Soft clipping effect using a cubic function with variable saturation.

    Nolan Jome
*/

#ifndef effect_softclip_h_
#define effect_softclip_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectSoftclip : public AudioStream
{
public:
    AudioEffectSoftclip() : AudioStream(1, inputQueueArray) {};
    virtual void update(void);
    void saturation(float sat);
private:
    audio_block_t *inputQueueArray[1];
    float saturate = 1.0;
};

#endif
