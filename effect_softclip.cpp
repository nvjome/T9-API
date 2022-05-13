/*
    Nolan Jome
*/

#include "Arduino.h"
#include "effect_softclip.h"

#define ONE_THIRD (0.333333f)
#define MAX_VAL_INT16 (32767.0f)

/*
    update()

    Update function called by the Audio library every update cycle.
*/
void AudioEffectSoftclip::update(void) {
    audio_block_t *block = receiveWritable();
    if (!block) return;

    int16_t *point = block->data;
    int16_t *end = block->data + AUDIO_BLOCK_SAMPLES;

    /*
    for(; point < end; point++) {
        int sample = *point;
        float temp = 0.0;
        // non-optimized cubic function
        temp = (float)sample / MAX_VAL_INT16;
        temp = temp - intense * ONE_THIRD * temp*temp*temp;

        *point = (int16_t)(temp*MAX_VAL_INT16);
    }
    */

    for(; point < end; point++) {
        if (*point > intense*MAX_VAL_INT16) {
            *point = intense*MAX_VAL_INT16;
        } else if (*point < -intense*MAX_VAL_INT16) {
            *point = -intense*MAX_VAL_INT16;
        }
    }

    transmit(block);
    release(block);

    return;
}

void AudioEffectSoftclip::intensity(float ints) {
    if (ints < 0.0f) {
        intense = 0.0f;
    } else if (ints > 1.0f) {
        intense = 1.0f;
    } else {
        intense = ints;
    }
}