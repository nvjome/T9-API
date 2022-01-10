/*
    Nolan Jome

    Contains all the function and global variable declarations.

    Procedure to add an effect:
        Add declarations for the parameter change functions.
        Modify the NUM_EFFECTS define statement.
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
#include "effect_class.h"

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

extern EffectClass* effectObjects_a[NUM_EFFECTS+1];

#endif