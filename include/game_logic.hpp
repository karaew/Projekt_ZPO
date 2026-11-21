//
// Created by konrad on 12.11.2026.
//

#ifndef APLIKACJA_TETRIS_GAME_LOGIC_HPP
#define APLIKACJA_TETRIS_GAME_LOGIC_HPP


#include "block.hpp"
#include "grid.hpp"

#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;

class GameLogic {
public:
    int score_;
    Window window_;
    char types[7] {'I', 'T', 'J', 'L', 'O', 's','z'};
    Figure figure_;

    GameLogic() : score_(0), figure_(types[random(0,7)]){};

    static int PixelToBlockX(int pos_x) ;
    static int PixelToBlockY(int pos_y) ;

    static int Block_To_PixelX(int pos_x, int pointer);
    static int Block_To_PixelY(int pos_y, int pointer) ;

    void set_Pixels_from_Block(const Block &block);

    void can_block_fall(int time);

    void can_block_move_R(int input);
    void can_block_move_L(int input);

    void new_figure() {
        figure_ = Figure(types[random(0,7)]);
    };
};

void refresh_window(const GameLogic &game);

#endif //APLIKACJA_TETRIS_GAME_LOGIC_HPP