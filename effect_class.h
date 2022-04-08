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
        int p1Min,
        int p1Max,
        int p2Min,
        int p2max,
        int p3Min,
        int p3Max,
        void (*modP1_fp)(int),
        void (*modP2_fp)(int),
        void (*modP3_fp)(int),
        void (*runStart_fp)(void),
        void (*runStop_fp)(void));
    
    void modParameter1(int param);
    void modParameter2(int param);
    void modParameter3(int param);
    void modParameterN(int sel, int param);

    void runOnStart(void);
    void runOnStop(void);

    std::string getEffectName(void);
    std::string getParameterName(int n);

    int getParameterNum(void);

    float getParameterMin(int param);
    float getParameterMax(int param);

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
    void (*modParameter1_fp)(int);
    void (*modParameter2_fp)(int);
    void (*modParameter3_fp)(int);

    // number of parameters
    int numParams;

    // parameters min/max
    int param1Min;
    int param1Max;
    int param2Min;
    int param2Max;
    int param3Min;
    int param3Max;
};

#endif