/*
    Nolan Jome

*/

#include "Arduino.h"
#include "T9_Pedal_Bundle.h"

void T9PB_begin(int memory) {

    sgtl5000.enable();
    sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000.lineInLevel(0);    // max input level
    //sgtl5000.lineOutLevel(13);  // max output level
    sgtl5000.volume(0.3);

    AudioMemory(memory);
}

