/*
    Nolan Jome

*/

#include "Arduino.h"
#include "effect01LPF_functions.h"

void T9PB_connect_effect_01(void) {
    effect01Input.connect();
    effect01Output.connect();
}

void T9PB_disconnect_effect_01(void) {
    effect01Input.disconnect();
    effect01Output.disconnect();
}

void T9PB_frequency(float freq) {
    effect01LPF.frequency(freq);
}