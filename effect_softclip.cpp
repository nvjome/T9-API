/*
    Nolan Jome
*/

#include "Arduino.h"
#include "effect_softclip.h"

#define ONE_THIRD (0.333333f)

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
        sample = sample - intense * ONE_THIRD * sample*sample*sample;

        *point = sample;
    }

    transmit(block);
    release(block);

    return;
}

void AudioEffectSoftclip::intensity(float ints) {
    if (ints < 0.0f) {
        intense = 0.0f;
    } else if (ints > 1.0) {
        intense = 1.0;
    } else {
        intense = ints;
    }
}