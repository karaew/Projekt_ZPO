#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "game_logic.hpp"

// Inicjalizacja ekranu SH1106 128x64 dla I2C
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
   Serial.begin(9600);
   u8g2.begin();

   randomSeed(analogRead(A0));
}

int current_frame = 0;
GameLogic game;
void loop() {

   if (current_frame > 60) {
      current_frame = 0;
   }
   game.can_block_fall(current_frame);
   refresh_window(game);
   current_frame ++;

   delay(1);
}