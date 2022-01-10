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
        const std::string& eName,
        const std::string& p1Name,
        const std::string& p2Name,
        const std::string& p3Name,
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

    std::string getEffectName(void);

private:
    // basic info
    std::string effectName;
    std::string param3Name;
    std::string param1Name;
    std::string param2Name;

    // connection object pointers
    AudioConnection* inputConn_p;
    AudioConnection* outputConn_p;

    // parameter change function pointers
    void (*modParameter1_fp)(float);
    void (*modParameter2_fp)(float);
    void (*modParameter3_fp)(float);

};

#endif