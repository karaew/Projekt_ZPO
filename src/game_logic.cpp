//
// Created by konrad on 12.11.2026.
//

#include "../include/game_logic.hpp"

std::vector<int> GameLogic::PixelToBlock(int const pos_x, int const pos_y) const {
    //wartosc 1 oraz 11 nadana z zalozeniem ze size_of_Block = 4
    int block_pos_x = pos_x/size_of_Block_ - 1;
    int block_pos_y = pos_y/size_of_Block_ - 11;
    return {block_pos_x, block_pos_y};
}

int GameLogic::BlockToPixel(int const pos_x, int const pos_y) const {

}
