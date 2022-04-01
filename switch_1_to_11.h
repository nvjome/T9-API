/*
    One input to ten output switch.
    The input can be passed to any individual output, allowing
    advanced audio routing without needing to (dis)connect
    AudioConnection objects.

    Nolan Jome
*/

#ifndef switch_1_to_11_h_
#define switch_1_to_11_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioSwitch1To11 : public AudioStream
{
public:
    AudioSwitch1To11() : AudioStream(1, inputQueueArray) {};
    virtual void update(void);
    void outputSelect(int chan);
private:
    audio_block_t* inputQueueArray[1];
    int channel = 0;
    const int outPortCnt = 10;
};

#endif
