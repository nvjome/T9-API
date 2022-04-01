/*
    Ten input to one output mux.
    The output can be driven by any individual output, allowing
    advanced audio routing without needing to (dis)connect
    AudioConnection objects.

    Nolan Jome
*/

#ifndef mux_11_to_1_h_
#define mux_11_to_1_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioMux11To1 : public AudioStream
{
public:
    AudioMux11To1() : AudioStream(inPortCnt, inputQueueArray) {};
    virtual void update(void);
    void inputSelect(int chan);
private:
    static const int inPortCnt = 10;
    audio_block_t* inputQueueArray[inPortCnt];
    int channel = 0;
};

#endif
