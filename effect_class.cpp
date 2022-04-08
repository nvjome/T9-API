/*
    Nolan Jome
*/

#include "effect_class.h"
#include <string>

EffectClass::EffectClass(
    const std::string& eName,
    const std::string& p1Name,
    const std::string& p2Name,
    const std::string& p3Name,
    int pNum,
    int p1Min,
    int p1Max,
    int p2Min,
    int p2Max,
    int p3Min,
    int p3Max,
    void (*modP1_fp)(int),
    void (*modP2_fp)(int),
    void (*modP3_fp)(int),
    void (*runStart_fp)(void),
    void (*runStop_fp)(void)) {
    // character arrays
    effectName = eName;
    param1Name = p1Name;
    param2Name = p2Name;
    param3Name = p3Name;

    // run on start/stop function pointers
    runOnStart_fp = runStart_fp;
    runOnStop_fp = runStop_fp;

    // parameter change function pointers
    modParameter1_fp = modP1_fp;
    modParameter2_fp = modP2_fp;
    modParameter3_fp = modP3_fp;

    numParams = pNum;

    // parameters min/max
    param1Min = p1Min;
    param1Max = p1Max;
    param3Max = p3Max;
    param2Min = p2Min;
    param2Max = p2Max;
    param3Min = p3Min;
}

void EffectClass::modParameter1(int param) {
    // call function pointed to
    modParameter1_fp(param);
}

void EffectClass::modParameter2(int param) {
    // call function pointed to
    modParameter2_fp(param);
}

void EffectClass::modParameter3(int param) {
    // call function pointed to
    modParameter3_fp(param);
}

void EffectClass::modParameterN(int sel, int param) {
    switch (sel) {
    case 1:
        modParameter1(param);
        break;
    case 2:
        modParameter2(param);
        break;
    case 3:
        modParameter3(param);
        break;
    default:
        ;
    }
}

void EffectClass::runOnStart(void) {
    // call function pointed to
    runOnStart_fp();
}

void EffectClass::runOnStop(void) {
    // call function pointed to
    runOnStop_fp();
}

std::string EffectClass::getEffectName(void) {
    return effectName;
}

std::string EffectClass::getParameterName(int n) {
    if (n == 1)
        return param1Name;
    else if (n == 2)
        return param2Name;
    else if (n == 3)
        return param3Name;
    else
        return "ERR";
}

int EffectClass::getParameterNum(void) {
    return numParams;
}

float EffectClass::getParameterMin(int param) {
    if (param == 1)
        return param1Min;
    else if (param == 2)
        return param2Min;
    else if (param == 3)
        return param3Min;
    else
        return 0.0;
}

float EffectClass::getParameterMax(int param) {
    if (param == 1)
        return param1Max;
    else if (param == 2)
        return param2Max;
    else if (param == 3)
        return param3Max;
    else
        return 0.0;
}
