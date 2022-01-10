/*
    Nolan Jome
*/

#include "effect_object.h"
#include <cstring>

EffectObject::EffectObject(
    char eName[16],
    char p1Name[10],
    char p2Name[10],
    char p3Name[10],
    AudioConnection* iConn_p,
    AudioConnection* oConn_p,
    void (*modP1_fp)(float),
    void (*modP2_fp)(float),
    void (*modP3_fp)(float))
{
    // character arrays
    strcpy(effectName,eName);
    strcpy(param1Name,p1Name);
    strcpy(param2Name,p2Name);
    strcpy(param3Name,p3Name);

    // connection object pointers
    inputConn_p = iConn_p;
    outputConn_p = oConn_p;

    // parameter change function pointers
    modParameter1_fp = modP1_fp;
    modParameter2_fp = modP2_fp;
    modParameter3_fp = modP3_fp;
}

void EffectObject::connect(void) {
    inputConn_p->connect();
    outputConn_p->connect();
}

void EffectObject::disconnect(void) {
    inputConn_p->disconnect();
    outputConn_p->disconnect();
}

void EffectObject::modParameter1(float param) {
    // call function pointed to
    modParameter1_fp(param);
}

void EffectObject::modParameter2(float param) {
    // call function pointed to
    modParameter2_fp(param);
}

void EffectObject::modParameter3(float param) {
    // call function pointed to
    modParameter3_fp(param);
}