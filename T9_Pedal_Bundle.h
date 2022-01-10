/*
    Nolan Jome

*/

#ifndef t9_pedal_bundle_h_
#define t9_pedal_bundle_h_

#include "Arduino.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_passthrough.h"

// Number of implemented effects, excluding bypass effect 0
#define NUM_EFFECTS 1

void T9PB_begin(void);
void T9PB_disconnect_all_effects(void);
void T9PB_hp_volume(float volume);
float T9PB_peak_detect(int source);


///////////////////////////////////////
// Effect switching functions
// Functions accept void arguments and return void.
///////////////////////////////////////

// Effect 0: Bypass
void T9PB_connect_effect_00(void);
void T9PB_disconnect_effect_00(void);

// Effect 1: Low Pass Filter
void T9PB_connect_effect_01(void);
void T9PB_disconnect_effect_01(void);


///////////////////////////////////////
// Effect parameter functions
///////////////////////////////////////

// Effect 1: Low Pass Filter
void T9PB_frequency(float freq);


///////////////////////////////////////
// Effect (dis)connect tables
///////////////////////////////////////
extern void (*T9PB_connectTable[NUM_EFFECTS+1])(void);

extern void (*T9PB_disconnectTable[NUM_EFFECTS+1])(void);

#endif