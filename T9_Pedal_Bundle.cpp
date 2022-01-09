/*
    Nolan Jome

*/

#include "Arduino.h"
#include "T9_Pedal_Bundle.h"

/*
    T9PB_begin
    Initializes the Teensy Audio library and settings
*/
void T9PB_begin(int memory) {
    T9PB_disconnect_all_cords();

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

// Effect 1: Low Pass Filter
void T9PB_connect_effect_01(void) {
    effect01Input.connect();
    effect01Output.connect();
}

void T9BP_disconnect_effect_01(void) {
    effect01Input.disconnect();
    effect01Output.disconnect();
}