#include <Arduino.h>
#include <U8g2lib.h>
#include "game_logic.hpp"

// Inicjalizacja ekranu SH1106 128x64 dla I2C
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


constexpr uint8_t BTN_PIN_R = 4;
constexpr uint8_t BTN_PIN_L = 2;
constexpr uint8_t BTN_PIN_Rotate = 3;

GameLogic* game = nullptr;

void setup() {
   Serial.begin(9600);
   u8g2.begin();

   u8g2.setDisplayRotation(U8G2_R3); // Obrót o 270 stopni

   randomSeed(2475123);
   game = new GameLogic();
   game -> new_figure();
   draw_frame();

   pinMode(BTN_PIN_R, INPUT_PULLUP);
   pinMode(BTN_PIN_L, INPUT_PULLUP);
   pinMode(BTN_PIN_Rotate, INPUT_PULLUP);
   u8g2.sendBuffer();
}

int current_frame = 0;

void loop() {
   if (current_frame > change_time) {
      current_frame = 0;
   }
   // char odebranyZnak = 0;
   // if (Serial.available() > 0) {
   //    odebranyZnak = Serial.read(); // Odczytaj jeden znak
   // }

   if (digitalRead(BTN_PIN_R) == LOW) {
      game -> can_block_move_R();
      refresh_window(*game);
   }
   if (digitalRead(BTN_PIN_L) == LOW) {
      game -> can_block_move_L();
      refresh_window(*game);
   }

   if (digitalRead(BTN_PIN_Rotate) == LOW) {
      game -> can_block_rotate();
      refresh_window(*game);
   }
   // if (odebranyZnak == '2') {
   //    digitalWrite(BTN_PIN_Fall, HIGH);
   //    game.can_block_fall(change_time);
   //    digitalWrite(BTN_PIN_Fall, LOW);
   // }

   game -> can_block_fall(current_frame);
   current_frame ++;
   delay(50);
}