/*
    Class to store information for a given effect.
    Does not include Teensy Audio objects, only wrapper information
    and functions for access by application code.

    Nolan Jome
*/

#ifndef effect_class_h_
#define effect_class_h_

#include <Arduino.h>
#include <Audio.h>
#include <string>

class EffectClass {
public:
    EffectClass(
        const std::string& eName,
        const std::string& p1Name,
        const std::string& p2Name,
        const std::string& p3Name,
        int pNum,
        void (*modP1_fp)(float),
        void (*modP2_fp)(float),
        void (*modP3_fp)(float),
        void (*runStart_fp)(void),
        void (*runStop_fp)(void));
    
    void modParameter1(float param);
    void modParameter2(float param);
    void modParameter3(float param);
    void modParameterN(int sel, float param);

    void runOnStart(void);
    void runOnStop(void);

    std::string getEffectName(void);
    std::string getParameterName(int n);

    int getParameterNum(void);

private:
    // basic info
    std::string effectName;
    std::string param1Name;
    std::string param2Name;
    std::string param3Name;

    // run on start/stop function pointers
    void (*runOnStart_fp)(void);
    void (*runOnStop_fp)(void);

    // parameter change function pointers
    void (*modParameter1_fp)(float);
    void (*modParameter2_fp)(float);
    void (*modParameter3_fp)(float);

    // number of parameters
    int numParams;
};

#endif