//
// Created by konrad on 12.11.2026.
//

#ifndef APLIKACJA_TETRIS_GAME_LOGIC_HPP
#define APLIKACJA_TETRIS_GAME_LOGIC_HPP

#include <vector>

#include <grid.hpp>
#include "block.hpp"

class GameLogic {
    int size_of_Block_;
    int score_;

    public:
    GameLogic(int const size_of_Block) : size_of_Block_(size_of_Block), score_(0) {};

    std::vector<int> PixelToBlock(int pos_x, int pos_y) const;

    int BlockToPixel(int pos_x, int pos_y) const;

    void is_block();
};

#endif //APLIKACJA_TETRIS_GAME_LOGIC_HPP