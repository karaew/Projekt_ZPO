//
// Created by konrad on 12.11.2026.
//

#ifndef APLIKACJA_TETRIS_GAME_LOGIC_HPP
#define APLIKACJA_TETRIS_GAME_LOGIC_HPP


#include "block.hpp"
#include "grid.hpp"
#include <Arduino.h>


class GameLogic {
    int score_;
    Window window_;
    GameBoard board_;
    char types[7] {'I', 'T', 'J', 'L', 'O', 's','z'};
    Figure figure_;
public:
    GameLogic(const Window &window, const GameBoard &board) : score_(0),  window_(window), board_(board), figure_(types[random(0,7)]){};

    static int PixelToBlockX(int pos_x) ;
    static int PixelToBlockY(int pos_y) ;

    static int BlockToPixelX(int pos_x, int pointer);
    static int BlockToPixelY(int pos_y, int pointer) ;

    void killPixels_from_Block(const Block &block);

    void can_block_fall(const Figure &figure, int time);

    void new_figure() {
        figure_ = Figure(types[random(0,7)]);
    };
};

#endif //APLIKACJA_TETRIS_GAME_LOGIC_HPP