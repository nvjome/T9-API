/*
    Nolan Jome

*/

#include "Arduino.h"
#include "T9_Pedal_Bundle.h"

/*
    T9PB_begin
    Initializes the Teensy Audio library and settings.

    NOTE: memory argument removed due to compilation error, apparently
    the argument for the AudioMemory macro needs to be a constant
    at compile time.
*/
void T9PB_begin(void) {
    T9PB_disconnect_all_effects();

    sgtl5000.enable();
    sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000.lineInLevel(0);    // max input level
    //sgtl5000.lineOutLevel(13);  // max output level
    sgtl5000.volume(0.3);

    //AudioMemory(memory);
}

///////////////////////////////////////
// Effect switching functions
// Functions accept void arguments and return void.
///////////////////////////////////////

// Effect 1: Low Pass Filter
void T9PB_connect_effect_01(void) {
    effect01Input.connect();
    effect01Output.connect();
}

void T9PB_disconnect_effect_01(void) {
    effect01Input.disconnect();
    effect01Output.disconnect();
}

// Effect 2: 


/*
    T9PB_disconnect_all_effects
    Disconnects all effects.

    TODO: May change to just iterating through an array of
    pointers to the AudioConnection objects that are the input
    and output connections to each effect.
*/
void T9PB_disconnect_all_effects(void) {
    for (int i = 0; i < NUM_EFFECTS; i++) {
        (*T9PB_disconnectTable[i])();
    }
}