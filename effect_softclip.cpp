/*
    Nolan Jome
*/

#include "Arduino.h"
#include "effect_softclip.h"

#define ONE_THIRD 0.33333333

/*
    update()

    Update function called by the Audio library every update cycle.
*/
void AudioEffectSoftclip::update(void) {
    audio_block_t *block = receiveWritable();
    if (!block) return;

    int16_t *point = block->data;
    int16_t *end = block->data + AUDIO_BLOCK_SAMPLES;

    for(; point < end; point++) {
        int sample = *point;

        // non-optimized cubic function
        //sample = sample - saturation * ONE_THIRD * sample*sample*sample;

        *point = sample;
    }

    transmit(block);
    release(block);

    return;
}

void AudioEffectSoftclip::saturation(float sat) {
    if (sat < 0.0f) {
        saturation = 0.0f;
    } else if (sat > 1.0f) {
        saturation = 1.0f;
    } else {
        saturation = sat;
    }
}