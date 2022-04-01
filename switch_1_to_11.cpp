/*
    Nolan Jome
*/

#include "Arduino.h"
#include "switch_1_to_11.h"

/*
    update()

    Update function called by the Audio library every update cycle.
*/
void AudioSwitch1To11::update(void) {
    audio_block_t *block;

    block = receiveReadOnly();
    if (!block) return;

    transmit(block, channel);
    release(block);

    return;
}

void AudioSwitch1To11::outputSelect(int chan) {
    if (chan >= 0 && chan < outPortCnt) {
        channel = chan;
    }
}