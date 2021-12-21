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

///////////////////////////////////////
// Audio Objects
// All audio objects for each effect, input, output, and others.
///////////////////////////////////////

// System input objects:
AudioInputI2S               lineIn;
AudioAmplifier              preGain;

// Effect 1: 


// Effect 2: 


// Effect 3: 


// Effect 4: 


// Effect 5: 


// Effect 6: 


// System output objects:
AudioAmplifier              postGain;
AudioOutputI2S              lineOut;

//Codec
AudioControlSGTL5000        sgtl5000;


///////////////////////////////////////
// Audio Cords
// ALL possible connections between objects.
// Use format for effects:  effectXXInput
//                          effectXXOutput
//                          effectXXSubYY
// Where XX is effect number and YY is another number for the effect sub connections.
// Effects may need multiple sub connections between objects in the effect.
// Use sensical fomat for other constant connections with postfix _c.
///////////////////////////////////////

AudioConnection             lineInToPreGain_c;
AudioConnection             postGainToLineOut_c;


///////////////////////////////////////
// Effect switching functions
///////////////////////////////////////

void T9PB_begin(int memory);
void T9PB_disconnectAllCords();
void T9PB_hp_volume(float volume) {
    sgtl5000.volume(volume);
}

// Effect 1: 
void T9PB_connect_effect_1();
void T9BP_disconnect_effect_1();
void T9BP_switch_effect_1();

// Effect 2: 

#endif