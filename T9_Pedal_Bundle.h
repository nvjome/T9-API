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
#include "switch_1_to_11.h"
#include "mux_11_to_1.h"
#include "effect_class.h"
#include "effect_softclip.h"

// Number of implemented effects, excluding bypass effect 0
#define NUM_EFFECTS 5

void T9PB_begin(void);
void T9PB_hp_volume(float volume);
float T9PB_peak_detect(int source);
int T9PB_change_effect(int curEffect, int newEffect);
std::string T9PB_get_effect_name(int effect);
std::string T9PB_get_parameter_name(int effect, int param);
int T9PB_change_parameter(int effect, int param, int value);
int T9PB_get_parameter_num(int effect);
int T9PB_get_parameter_min(int effect, int param);
int T9PB_get_parameter_max(int effect, int param);


///////////////////////////////////////
// Effect parameter functions
///////////////////////////////////////

// Null functions, used for empty parameters
// Would ideally be optimized away, but not sure.
void nullFunc(float n);
void nullFunc(int n);
void nullFunc(void);

// Effect 1: Low Pass Filter
void T9PB_effect01_frequency(int freq);

// Effect 2: Freeverb
void T9PB_effect02_roomsize(int size);
void T9PB_effect02_damping(int damp);
void T9PB_effect02_wetdry(int wet);
void T9PB_effect02_start(void);

// Effect 3: Tremolo
void T9PB_effect03_depth(int dep);
void T9PB_effect03_rate(int rate);
void T9PB_effect03_start(void);

// Effect 4: Delay
void T9PB_effect04_time(int t);
void T9PB_effect04_gain(int gain);
void T9PB_effect04_start(void);
void T9PB_effect04_stop(void);

// Effect 5: Saturation
void T9PB_effect05_intensity(int intense);


///////////////////////////////////////
// Effect object pointer array
///////////////////////////////////////

extern EffectClass* effectObjects_a[NUM_EFFECTS+1];

#endif