//
// Created by konrad on 12.11.2026.
//

#ifndef APLIKACJA_TETRIS_GAME_LOGIC_HPP
#define APLIKACJA_TETRIS_GAME_LOGIC_HPP

#include <utility>
#include <vector>

#include "block.hpp"
#include "grid.hpp"


class GameLogic {
    int score_;
    Window window_;
    GameBoard board_;
    public:
    GameLogic(Window window, GameBoard board) : score_(0),  window_(std::move(window)), board_(std::move(board)) {};

    std::vector<int> PixelToBlock(int pos_x, int pos_y) const;

    std::vector<std::vector<int>> BlockToPixel(int pos_x, int pos_y) const;

    void can_block_fall(const Figure &figure);

};

#endif //APLIKACJA_TETRIS_GAME_LOGIC_HPP