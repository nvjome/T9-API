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
    AudioConnection* iConn_p,
    AudioConnection* oConn_p,
    void (*modP1_fp)(float),
    void (*modP2_fp)(float),
    void (*modP3_fp)(float))
{
    // character arrays
    effectName = eName;
    param1Name = p1Name;
    param2Name = p2Name;
    param3Name = p3Name;

    // connection Class pointers
    inputConn_p = iConn_p;
    outputConn_p = oConn_p;

    // parameter change function pointers
    modParameter1_fp = modP1_fp;
    modParameter2_fp = modP2_fp;
    modParameter3_fp = modP3_fp;
}

void EffectClass::modParameter1(float param) {
    // call function pointed to
    modParameter1_fp(param);
}

void EffectClass::modParameter2(float param) {
    // call function pointed to
    modParameter2_fp(param);
}

void EffectClass::modParameter3(float param) {
    // call function pointed to
    modParameter3_fp(param);
}

void EffectClass::connect(void) {
    inputConn_p->connect();
    outputConn_p->connect();
}

void EffectClass::disconnect(void) {
    inputConn_p->disconnect();
    outputConn_p->disconnect();
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
}