#include <Arduino.h>
//20Bit + 4bit command protocol
//316 uS + 1024 uS
//No sart bit but bit0 at end
//Allarme maurizio  0x1a012


class Akhan100f14 {
public:
    void SendCode(uint32_t codice, uint8_t txpin);
private:
    const uint16_t period = 316;
    const uint32_t SeqDelay = (period*3.25)*10+100;
    void SendBit0(uint8_t txpin){
        digitalWrite(txpin, HIGH);
        delayMicroseconds(period);
        //Mando il segnale per Fosc*2
        digitalWrite(txpin, LOW);
        delayMicroseconds(period*3.25);
    }
    void SendBit1(uint8_t txpin){
        digitalWrite(txpin, HIGH);
        delayMicroseconds(period*3.25);
        //Mando il segnale per Fosc*2
        digitalWrite(txpin, LOW);
        delayMicroseconds(period);
    }
};


void Akhan100f14::SendCode(uint32_t codice, uint8_t txpin){
    for(uint8_t seq = 0; seq < 3; seq++){
        //Prendo 12bit uno ad uno
        for (int8_t i = 23; i >= 0; i--) {
            uint8_t bit = ((codice >> i) & 1);
            if(bit == 0){
                SendBit0(txpin);
            }else{
                SendBit1(txpin);
            }
        }
        SendBit0(txpin);
        delayMicroseconds(SeqDelay);
    }
}