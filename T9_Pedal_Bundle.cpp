/*
    Nolan Jome

*/

#include "Arduino.h"
#include "T9_Pedal_Bundle.h"

/*
    T9PB_begin
    Initializes the Teensy Audio library and settings.
    Arguments
        memory: number of audio blocks to allocate for Teensy Audio library
*/
void T9PB_begin(int memory) {
    T9PB_disconnect_all_effects();

    sgtl5000.enable();
    sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000.lineInLevel(0);    // max input level
    //sgtl5000.lineOutLevel(13);  // max output level
    sgtl5000.volume(0.3);

    AudioMemory(memory);
}

///////////////////////////////////////
// Effect switching functions
// Functions accept void arguments and return void.
///////////////////////////////////////
// Moved to individual source files.


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