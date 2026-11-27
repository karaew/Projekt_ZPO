//
// Created by konrad on 12.11.2026.
//

#ifndef APLIKACJA_TETRIS_GAME_LOGIC_HPP
#define APLIKACJA_TETRIS_GAME_LOGIC_HPP


#include "block.hpp"
#include "grid.hpp"

#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

class GameLogic {
public:
    int score_;
    Window window_;
    char types[7] {'I', 'T', 'J', 'L', 'O', 's','z'};
    Figure figure_;
    Figure next_figure_;

    GameLogic() : score_(0), figure_(types[random(0,7)]), next_figure_(types[random(0,7)]) {
        next_figure_.kill_blocks();
    };

    static int PixelToBlockX(int pos_x) ;
    static int PixelToBlockY(int pos_y) ;

    static int Block_To_PixelX(int pos_x, int pointer);
    static int Block_To_PixelY(int pos_y, int pointer) ;

    void set_Pixels_from_Block(const Block &block);

    void can_block_fall(int time);

    bool can_block_move_R();
    bool can_block_move_L();

    void can_block_rotate();

    void display_next_figure();
    void new_figure();
};

void refresh_window(GameLogic &game);
void clear_lane(GameLogic &game, int row_y);

void draw_frame();

#endif //APLIKACJA_TETRIS_GAME_LOGIC_HPP