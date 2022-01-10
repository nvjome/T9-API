/*
    Nolan Jome

*/

#ifndef t9_pedal_bundle_h_
#define t9_pedal_bundle_h_

#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "effect_passthrough.h"
#include "effect_object.h"

// Number of implemented effects, excluding bypass effect 0
#define NUM_EFFECTS 2

void T9PB_begin(void);
void T9PB_disconnect_all_effects(void);
void T9PB_hp_volume(float volume);
float T9PB_peak_detect(int source);


///////////////////////////////////////
// Effect parameter functions
///////////////////////////////////////

// Null function, used for empty parameters
// Would ideally be optimized away, but not sure.
void nullFunc(float n);

// Effect 1: Low Pass Filter
void T9PB_effect01_frequency(float freq);

// Effect 2: Freeverb
void T9PB_effect02_roomsize(float size);
void T9PB_effect02_damping(float damp);


///////////////////////////////////////
// Effect object pointer array
///////////////////////////////////////

extern EffectObject* effectObjects_a[NUM_EFFECTS+1];

#endif