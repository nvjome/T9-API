/*
    Nolan Jome
*/

#include "Arduino.h"
#include "mux_11_to_1.h"

/*
    update()

    Update function called by the Audio library every update cycle.
*/
void AudioMux11To1::update(void) {
    audio_block_t *block;

    block = receiveReadOnly(channel);
    if (!block) return;

    transmit(block);
    release(block);

    return;
}

void AudioMux11To1::inputSelect(int chan) {
    if (chan >= 0 && chan < inPortCnt) {
        channel = chan;
    }
}