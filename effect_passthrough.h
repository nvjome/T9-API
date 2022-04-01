/*
    Simple audio passthrough object. Useful for bypassing other effects perhaps,
    but maybe more useful as an audio block template.

    Nolan Jome
*/

#ifndef effect_passthrough_h_
#define effect_passthrough_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectPassthrough : public AudioStream
{
public:
    AudioEffectPassthrough() : AudioStream(1, inputQueueArray) {};
    virtual void update(void);
private:
    audio_block_t *inputQueueArray[1];
};

#endif
