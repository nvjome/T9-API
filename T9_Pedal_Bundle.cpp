/*
    Nolan Jome

*/

#include "Arduino.h"
#include "T9_Pedal_Bundle.h"

///////////////////////////////////////
// Audio Objects
// All audio objects for each effect, input, output, and others.
// Use format for effects:  effectXXShortBlockName
// Where XX is effect number.
///////////////////////////////////////

// System input objects:
AudioInputI2S               lineIn;
AudioAmplifier              preGain;

// Effect 1: Low Pass Filter
AudioFilterStateVariable    effect01LPF;

// Effect 2: 


// Effect 3: 


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
// The first audio block's input is the output of the preGain block.
// The last audio block's output is the input of the postGain block.
// Effects may need multiple sub connections between objects in the effect.
// Use sensical fomat for other constant connections with postfix _c.
///////////////////////////////////////

AudioConnection             lineInToPreGain_c(lineIn, 0, preGain, 0);
AudioConnection             postGainToLineOut_c(postGain, 0, lineOut, 0);

// Effect 1: Low Pass Filter
AudioConnection             effect01Input(preGain, 0, effect01LPF, 0);
AudioConnection             effect01Output(effect01LPF, 0, postGain, 0);


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

void T9PB_hp_volume(float volume) {
    sgtl5000.volume(volume);
}


///////////////////////////////////////
// Effect switching functions
// Functions accept void arguments and return void.
///////////////////////////////////////

// Effect 1: Low Pass Filter
void T9PB_connect_effect_01(void) {
    //effect01Input.connect();
    //effect01Output.connect();
}

void T9PB_disconnect_effect_01(void) {
    //effect01Input.disconnect();
    //effect01Output.disconnect();
}

// Effect 2: 



///////////////////////////////////////
// Effect parameter functions
///////////////////////////////////////

// Effect 1: Low Pass Filter
void T9PB_frequency(float freq) {
    effect01LPF.frequency(freq);
}


///////////////////////////////////////
// Effect (dis)connect tables
///////////////////////////////////////

void (*T9PB_connectTable[NUM_EFFECTS])(void) = {
    T9PB_connect_effect_01
};

void (*T9PB_disconnectTable[NUM_EFFECTS])(void) = {
    T9PB_connect_effect_01
};


