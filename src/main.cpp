#include <Arduino.h>
//#include <Adafruit_GFX.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
//#include <FS.h>
//#include <SPIFFS.h>
#include <Bruteforce.hpp>

#define TXPIN GPIO_NUM_12
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4 

Bruteforce brute = Bruteforce(TXPIN, 330);

//Adafruit_SSD1306 lcd = Adafruit_SSD1306(128, 160, TFT_MOSI, TFT_SCLK, TFT_DC, TFT_RST, TFT_CS);
TFT_eSPI lcd = TFT_eSPI();

void setup() {
    lcd.begin();
    lcd.setCursor(0, 0);
    lcd.fillScreen(TFT_BLACK);
    lcd.setRotation(2);
    Serial.begin(115200);
    // put your setup code here, to run once:
    pinMode(TXPIN, OUTPUT);
}

void loop() {
    for(uint16_t i = 1; i <= 4096; i++){
        brute.SendCode(i);
        lcd.fillRect(0, 0, 100, 20, TFT_BLACK);
        lcd.setCursor(0, 0);
        lcd.printf("Code: %d", i);
    }
    //brute.akhan100f14.SendCode(10509473, TXPIN);
    //brute.SendCode(3804);
    //SendCode(1350);//Parco piro
    //brute.SendCode(3805);//Giulio
    /* uint16_t period = 300;
    for(int i = 0; i <= 20; i++){
        brute.SendDebruijn();
        delay(1000);
        period += 10;
        brute.SetPeriod(period);
    } */
    //brute.SendDebruijn();
    while(true){
        delay(1000);
    }
}