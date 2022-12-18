#include <Arduino.h>
#include <inttypes.h>
#include <Akhan100f14.hpp>
#include <debruijn_sequences.hpp>


class Bruteforce {
public:
    Akhan100f14 akhan100f14;
    //Protocolli
    Bruteforce(uint8_t _txpin, uint16_t _Period){
        this->txpin = _txpin;
        this->period = _Period;
        this->SeqDelay = (_Period*3)*12+200;
    }
    void SendCode(uint16_t codice);
    void SendDebruijn();
    void SetPeriod(uint16_t _Period);
private:
    uint16_t period;
    uint8_t txpin;
    uint16_t SeqDelay;
    void SendBit0(){
        digitalWrite(txpin, LOW);
        //Non mando nulla per 333microsecondi cioè 1 Fosc
        delayMicroseconds(period);
        //Mando il segnale per Fosc*2
        digitalWrite(txpin, HIGH);
        delayMicroseconds(period*2);
        digitalWrite(txpin, LOW);
    }
    void SendBit1(){
        digitalWrite(txpin, LOW);
        //Non mando nulla per Fosc*2
        delayMicroseconds(period*2);
        //Mando il segnale per 1 Fosc
        digitalWrite(txpin, HIGH);
        delayMicroseconds(period);
        digitalWrite(txpin, LOW);
    }
    void SendStartBit(){
        digitalWrite(txpin, LOW);
        //Non mando nulla per 1 Fosc
        delayMicroseconds(period);
        //Mando il segnale per 1 Fosc
        digitalWrite(txpin, HIGH);
        delayMicroseconds(period);
        digitalWrite(txpin, LOW);
    }
};

void Bruteforce::SendCode(uint16_t codice){
    for(uint8_t seq = 0; seq < 3; seq++){
        //Invio lo start bit
        SendStartBit();
        //Prendo 12bit uno ad uno
        for (uint8_t i = 0; i <= 11; i++) {
            uint8_t bit = ((codice >> i) & 1);
            if(bit == 0){
                SendBit0();
            }else{
                SendBit1();
            }
        }
        delayMicroseconds(12000);
    }
}

void Bruteforce::SendDebruijn(){
    SendStartBit();
    for(int i = 0; i < sizeof(debruijn_12bit); i++){
        if( debruijn_12bit[i] == 0 ){
            SendBit0();
        }else{
            SendBit1();
        }
    }
}

void Bruteforce::SetPeriod(uint16_t _Period){
    this->period = _Period;
    this->SeqDelay = (_Period*3)*12+100;
}