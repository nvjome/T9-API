/*
    Nolan Jome

    Contains all function and global variable definitions.
    Also creates the EffectClass objects for each effect,
    and the EffectClass object pointer array.

    Procedure to add an effect:
        Add the Teensy Audio objects definitions.
        Add the Teensy Audio connection definitions.
        Add parameter change functions for each effect parameter.
        Create EffectClass object.
        Append new EffectClass object to pointer array.
*/

#include <Arduino.h>
#include "T9_Pedal_Bundle.h"
#include "effect_class.h"

///////////////////////////////////////
// Audio Objects
// All audio objects for each effect, input, output, and others.
// Use format for effects:  effectXXShortBlockName
// Where XX is effect number.
///////////////////////////////////////

// System input objects:
//AudioInputUSB               lineIn;
AudioInputI2S               lineIn;
AudioAmplifier              preGain;
AudioSwitch1To11            inputSwitch;

// Effect 0: Bypass
AudioEffectPassthrough      effect00Bypass;

// Effect 1: Low Pass Filter
AudioFilterStateVariable    effect01LPF;

// Effect 2: Freeverb
AudioEffectPassthrough      effect02Buffer;
AudioEffectFreeverb         effect02Freeverb;
AudioMixer4                 effect02Mixer;

// Effect 3:  Tremolo
AudioSynthWaveformDc        effect03Dc;
AudioSynthWaveformSine      effect03Sine;
AudioMixer4                 effect03Mixer;
AudioEffectMultiply         effect03Multiply;

// Effect 4: Delay
AudioMixer4                 effect04Mixer;
AudioEffectDelay            effect04Delay;
AudioAmplifier              effect04Amp;

// System output objects:
AudioAmplifier              postGain;
AudioMux11To1               outputMux;
AudioOutputI2S              lineOut;

// Peak detection blocks
AudioAnalyzePeak            lineInPeak;
AudioAnalyzePeak            lineOutPeak;

//Codec
AudioControlSGTL5000        sgtl5000;


///////////////////////////////////////
// Audio Connections
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

// Pre-effect connections

AudioConnection             lineInToPreGain_c(lineIn, 0, preGain, 0);
AudioConnection             lineInToPeakL_c(lineIn, 0, lineInPeak, 0);
AudioConnection             preGainToSwitch(preGain, 0, inputSwitch, 0);

// Post-effect connections

AudioConnection             muxToPostGain(outputMux, 0, postGain, 0);
AudioConnection             postGainToLineOutL_c(postGain, 0, lineOut, 0);
AudioConnection             postGainToLineOutR_c(postGain, 0, lineOut, 1);
AudioConnection             postGainToPeak_c(postGain, 0, lineOutPeak, 0);

// Effect 0: Bypass
AudioConnection             effect00Input(inputSwitch, 0, effect00Bypass, 0);
AudioConnection             effect00Output(effect00Bypass, 0, outputMux, 0);

// Effect 1: Low Pass Filter
AudioConnection             effect01Input(inputSwitch, 1, effect01LPF, 0);
AudioConnection             effect01Output(effect01LPF, 0, outputMux, 1);

// Effect 2: Freeverb
AudioConnection             effect02Input(inputSwitch, 2, effect02Buffer, 0);
AudioConnection             effect02Sub01(effect02Buffer, 0, effect02Mixer, 0);
AudioConnection             effect02Sub02(effect02Buffer, 0, effect02Freeverb, 0);
AudioConnection             effect02Sub03(effect02Freeverb, 0, effect02Mixer, 1);
AudioConnection             effect02Output(effect02Mixer, 0, outputMux, 2);

// Effect 3: Tremolo
AudioConnection             effect03Input(inputSwitch, 3, effect03Multiply, 1);
AudioConnection             effect03Sub01(effect03Dc, 0, effect03Mixer, 0);
AudioConnection             effect03Sub02(effect03Sine, 0, effect03Mixer, 1);
AudioConnection             effect03Sub03(effect03Mixer, 0, effect03Multiply, 0);
AudioConnection             effect03Output(effect03Multiply, 0, outputMux, 3);

// Effect 4: Delay
AudioConnection             effect04Input(inputSwitch, 4, effect04Mixer, 0);
AudioConnection             effect04Sub01(effect04Mixer, 0, effect04Amp, 0);
AudioConnection             effect04Sub02(effect04Amp, 0, effect04Delay, 0);
AudioConnection             effect04Sub03(effect04Delay, 0, effect04Mixer, 1);
AudioConnection             effect04Output(effect04Mixer, 0, outputMux, 4);

/*
    T9PB_begin
    Initializes the Teensy Audio library and settings.

    NOTE: memory argument removed due to compilation error,
    the argument for the AudioMemory macro needs to be a constant
    at compile time.
*/
void T9PB_begin(void) {
    // default software passthrough
    inputSwitch.outputSelect(0);
    outputMux.inputSelect(0);

    sgtl5000.enable();
    sgtl5000.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000.lineInLevel(0);    // max input level
    sgtl5000.lineOutLevel(13);  // max output level
    sgtl5000.volume(0.3);

    preGain.gain(1.0);
    postGain.gain(1.0);
}

void T9PB_hp_volume(float volume) {
    sgtl5000.volume(volume);
}

/*
    T9PB_peak_detect
    Checks for peaks at the input or output.
    Arguments:
        source: Where to check for peak, 0 checks input, 1 checks output.
    Returns:
        The greatest sample value since the last check, 0.0 to 1.0 float.
*/
float T9PB_peak_detect(int source) {
    float ret = 0.0;
    if (source == 0) {
        if (lineInPeak.available()) {
            ret = lineInPeak.read();
        }
    } else if (source == 1) {
        if (lineOutPeak.available()) {
            ret = lineOutPeak.read();
        }
    }
    return ret;
}

/*
    T9PB_change_effect
    Controls input switch and output mux to change effects.
    Arguments:
        curEffect: Effect to turn off.
        newEffect: Effect to turn on.
    Returns:
        Active effect, or -1 for error.
*/
int T9PB_change_effect(int curEffect, int newEffect) {
    int ret = -1;
    if (newEffect >= 0 && newEffect <= NUM_EFFECTS) {
        // run on stop function
        effectObjects_a[curEffect]->runOnStop();
        // switch output
        outputMux.inputSelect(newEffect);
        // switch input
        inputSwitch.outputSelect(newEffect);
        // run on start function
        effectObjects_a[newEffect]->runOnStart();
        ret = newEffect;
    }
    return ret;
}

/*
    T9PB_get_effect_name
    Getter function for effect names.
    Arguments:
        effect: Effect index, 0 to NUM_EFFECTS.
    Returns:
        Effect name as string.
*/
std::string T9PB_get_effect_name(int effect) {
    if (effect <= NUM_EFFECTS && effect >= 0) {
        return effectObjects_a[effect]->getEffectName();
    } else {
        return "ERR";
    }
}

/*
    T9PB_get_parameter_name
    Getter function for parameter names.
    Arguments:
        effect: Effect index, 0 to NUM_EFFECTS.
        param: Parameter index, 1 to 3.
    Returns:
        Parameter name as string.
*/
std::string T9PB_get_parameter_name(int effect, int param) {
    if (effect <= NUM_EFFECTS && effect >= 0) {
        if (param <= 3 && param > 0) {
            return effectObjects_a[effect]->getParameterName(param);
        } else {
            return "ERR";
        }
    } else {
        return "ERR";
    }
}

int T9PB_change_parameter(int effect, int param, float value) {
    int ret = -1;
    if (effect <= NUM_EFFECTS && effect >= 0) {
        if (param <= 3 && param > 0) {
            effectObjects_a[effect]->modParameterN(param, value);
            ret = 0;
        }
    }
    return ret;
}

int T9PB_get_parameter_num(int effect) {
    if (effect >= 0 && effect <= NUM_EFFECTS) {
        return effectObjects_a[effect]->getParameterNum();
    } else {
        return 0;
    }
}

int T9PB_get_parameter_min(int effect, int param) {
    if (effect >= 0 && effect <= NUM_EFFECTS) {
        return effectObjects_a[effect]->getParameterMin(param);
    } else {
        return 0;
    }
}

int T9PB_get_parameter_max(int effect, int param) {
    if (effect >= 0 && effect <= NUM_EFFECTS) {
        return effectObjects_a[effect]->getParameterMax(param);
    } else {
        return 0;
    }
}


///////////////////////////////////////
// Effect parameter functions
///////////////////////////////////////

// Null function, used for empty parameters
// Would ideally be optimized away, but not sure.
void nullFunc(float n) {}
void nullFunc(int n) {}
void nullFunc(void) {}

// Effect 1: Low Pass Filter
#define E1_MIN_FREQ 20
#define E1_MAX_FREQ 5000
void T9PB_effect01_frequency(int freq) {
    // better handles out of bound input by clamping to the min/max
    if (freq <= E1_MIN_FREQ) {
        effect01LPF.frequency((float)(E1_MIN_FREQ));
    } else if (freq >= E1_MAX_FREQ) {
        effect01LPF.frequency((float)(E1_MAX_FREQ));
    } else {
        effect01LPF.frequency((float)freq);
    }
}

// Effect 2: Freeverb
float effect02_wet = 0.5;
void T9PB_effect02_roomsize(int size) {
    //effect02Freeverb.roomsize(size);
    // better handles out of bound input by clamping to the min/max
    if (size <= 0) {
        effect02Freeverb.roomsize(0.0);
    } else if (size >= 100) {
        effect02Freeverb.roomsize(1.0);
    } else {
        effect02Freeverb.roomsize((float)size/100.0);
    }
}

void T9PB_effect02_damping(int damp) {
    //effect02Freeverb.damping(damp);
    // better handles out of bound input by clamping to the min/max
    if (damp <= 0) {
        effect02Freeverb.damping(0.0);
    } else if (damp >= 100) {
        effect02Freeverb.damping(1.0);
    } else {
        effect02Freeverb.damping((float)damp/100.0);
    }
}

void T9PB_effect02_wetdry(int wet) {
    if (wet <= 0) {
        // full dry
        effect02Mixer.gain(0,1.0);
        effect02Mixer.gain(1,0.0);
        effect02_wet = 0.0;
    } else if (wet >= 100) {
        // full wet
        effect02Mixer.gain(0,0.0);
        effect02Mixer.gain(0,1.0);
        effect02_wet = 1.0;
    } else {
        float wet_f = ((float)wet/100.0);
        // "dry" gain
        effect02Mixer.gain(0,wet_f-1.0);
        // "wet" gain
        effect02Mixer.gain(1,wet_f);
        effect02_wet = wet_f;
    }
}

void T9PB_effect02_start(void) {
    // default gain values
    effect02Mixer.gain(0, 1.0-effect02_wet);
    effect02Mixer.gain(1, effect02_wet);
}

// Effect 3: Tremolo
float effect03_depth = 0.1;
float effect03_rate = 5;
#define E3_MAX_RATE 100
void T9PB_effect03_depth(int dep) {
    if (dep <= 0) {
        effect03Dc.amplitude(1.0);
        effect03Sine.amplitude(0);
        effect03_depth = 0.0;
    } else if (dep >= 100) {
        effect03Dc.amplitude(0);
        effect03Sine.amplitude(1.0);
        effect03_depth = 1.0;
    } else {
        float dep_f = (float)dep/100.0;
        effect03Dc.amplitude(1.0 - dep_f);
        effect03Sine.amplitude(dep_f);
        effect03_depth = dep_f;
    }
}

void T9PB_effect03_rate(int rate) {
    if (rate <= 0) {
        effect03Sine.frequency(0.0);
        effect03_rate = 0.0;
    } else if (rate >= E3_MAX_RATE) {
        effect03Sine.frequency((float)E3_MAX_RATE);
        effect03_rate = E3_MAX_RATE;
    } else {
        effect03Sine.frequency((float)rate);
        effect03_rate = rate;
    }
}

void T9PB_effect03_start(void) {
    T9PB_effect03_depth(effect03_depth);
    T9PB_effect03_rate(effect03_rate);
}

// Effect 4: Delay
#define E4_MAX_DELAY_TIME 1000 // ms
#define E4_MIN_DELAY_TIME 0   // ms
float effect04_time = 100.0;
float effect04_gain = 0.5;

void T9PB_effect04_time(int t) {
    if (t <= E4_MIN_DELAY_TIME) {
        effect04Delay.delay(0, E4_MIN_DELAY_TIME);
        effect04_time = E4_MIN_DELAY_TIME;
    } else if (t >= E4_MAX_DELAY_TIME) {
        effect04Delay.delay(0, E4_MAX_DELAY_TIME);
        effect04_time = E4_MAX_DELAY_TIME;
    } else {
        effect04Delay.delay(0, (float)t);
        effect04_time = (float)t;
    }
}

void T9PB_effect04_gain(int gain) {
    if (gain <= 0) {
        effect04Amp.gain(0.0);
        effect04_gain = 0.0;
    } else if (gain >= 99) {
        // limit gain somewhat at least
        effect04Amp.gain(0.99);
        effect04_gain = 0.99;
    } else {
        float gain_f = (float)gain/100.0;
        effect04Amp.gain(gain_f);
        effect04_gain = gain_f;
    }
}

void T9PB_effect04_start(void) {
    T9PB_effect04_gain(effect04_gain);
    T9PB_effect04_time(effect04_time);
}

void T9PB_effect04_stop(void) {
    effect04Delay.disable(0);
}

///////////////////////////////////////
// Effect objects
// Each EffectClass object needs the following:
//      Effect name
//      Parameter name(s)
//      Parameter change function pointers
//      Run on start and stop function pointers
///////////////////////////////////////

// Effect 0: Bypass
EffectClass effect00Bypass_o(
    "Bypass", "NA", "NA", "NA", 0,
    0, 0, 0, 0, 0, 0,
    nullFunc, nullFunc, nullFunc,
    nullFunc, nullFunc
);

// Effect 1: Low Pass Filter
EffectClass effect01LPF_o(
    "LPF", "Frequency", "NA", "NA", 1,
    E1_MIN_FREQ, E1_MAX_FREQ, 0, 0, 0, 0,
    T9PB_effect01_frequency, nullFunc, nullFunc,
    nullFunc, nullFunc

);

// Effect 2: Freeverb
EffectClass effect02Freeverb_o(
    "Freeverb", "Roomsize", "Damping", "Wet/Dry", 3,
    0, 100, 0, 100, 0, 100,
    T9PB_effect02_roomsize, T9PB_effect02_damping, T9PB_effect02_wetdry,
    T9PB_effect02_start, nullFunc
);

// Effect 3: Tremolo
EffectClass effect03Tremolo_o(
    "Tremelo", "Depth", "Rate", "NA", 2,
    0, 100, 0, E3_MAX_RATE, 0, 0,
    T9PB_effect03_depth, T9PB_effect03_rate, nullFunc,
    T9PB_effect03_start, nullFunc
);

// Effect 4: Delay
EffectClass effect04Delay_o(
    "Delay", "Time", "Gain", "NA", 2,
    E4_MIN_DELAY_TIME, E4_MAX_DELAY_TIME, 0, 100, 0, 0,
    T9PB_effect04_time, T9PB_effect04_gain, nullFunc,
    T9PB_effect04_start, T9PB_effect04_stop
);


///////////////////////////////////////
// Effect object pointer array
///////////////////////////////////////

EffectClass* effectObjects_a[NUM_EFFECTS+1] = {
    &effect00Bypass_o,
    &effect01LPF_o,
    &effect02Freeverb_o,
    &effect03Tremolo_o,
    &effect04Delay_o
};