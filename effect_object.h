/*
    Nolan Jome
*/

#ifndef effect_object_h_
#define effect_object_h_

#include <Arduino.h>
#include <Audio.h>
#include <string>

class EffectObject {
public:
    EffectObject(
        char eName[16],
        char p1Name[10],
        char p2Name[10],
        char p3Name[10],
        AudioConnection* iConn_p,
        AudioConnection* oConn_p,
        void (*modP1_fp)(float),
        void (*modP2_fp)(float),
        void (*modP3_fp)(float));
    
    void modParameter1(float param);
    void modParameter2(float param);
    void modParameter3(float param);

    void connect(void);
    void disconnect(void);

private:
    // basic info
    char effectName[16];
    char param1Name[10];
    char param2Name[10];
    char param3Name[10];

    // connection object pointers
    AudioConnection* inputConn_p;
    AudioConnection* outputConn_p;

    // parameter change function pointers
    void (*modParameter1_fp)(float);
    void (*modParameter2_fp)(float);
    void (*modParameter3_fp)(float);

};

#endif