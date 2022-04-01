/*
    Nolan Jome
*/

#include "Arduino.h"
#include "effect_passthrough.h"

/*
    update

    Update function called by the Audio library every update cycle.
    Simply receives in the sample block and transmits it.
*/
void AudioEffectPassthrough::update(void) {
    audio_block_t *block;

    block = receiveReadOnly();
    if (!block) return;

    transmit(block);
    release(block);

    return;
}