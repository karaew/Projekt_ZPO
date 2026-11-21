#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Inicjalizacja ekranu SH1106 128x64 dla I2C (tryb pełnego bufora)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
   Serial.begin(9600);
   u8g2.begin();
}

void loop() {

}