#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "game_logic.hpp"

// Inicjalizacja ekranu SH1106 128x64 dla I2C
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


constexpr int LED_PIN_R = 12;
constexpr int LED_PIN_L = 11;
constexpr int LED_PIN_Rotate = 10;
constexpr int LED_PIN_Fall = 9;
GameLogic game;

void setup() {
   Serial.begin(9200);
   u8g2.begin();

   randomSeed(2137);

   game.new_figure();



   pinMode(LED_PIN_R, OUTPUT);
   pinMode(LED_PIN_L, OUTPUT);
   pinMode(LED_PIN_Rotate, OUTPUT);
   pinMode(LED_PIN_Fall, OUTPUT);
}

int current_frame = 0;

void loop() {

   if (current_frame > change_time) {
      current_frame = 0;
   }

   if (Serial.available() > 0) {
      char odebranyZnak = Serial.read(); // Odczytaj jeden znak


      if (odebranyZnak == '6') {
         digitalWrite(LED_PIN_R, HIGH);
         game.can_block_move_R();
         digitalWrite(LED_PIN_R, LOW);
         refresh_window(game);
      }
      if (odebranyZnak == '4') {
         digitalWrite(LED_PIN_L, HIGH);
         game.can_block_move_L();
         digitalWrite(LED_PIN_L, LOW);
         refresh_window(game);
      }

      if (odebranyZnak == '5') {
         digitalWrite(LED_PIN_Rotate, HIGH);
         game.can_block_rotate();
         digitalWrite(LED_PIN_Rotate, LOW);
         refresh_window(game);
      }
      if (odebranyZnak == '2') {
         digitalWrite(LED_PIN_Fall, HIGH);
         game.can_block_fall(change_time);
         digitalWrite(LED_PIN_Fall, LOW);
      }
   }

   game.can_block_fall(current_frame);
   refresh_window(game);
   current_frame ++;

}