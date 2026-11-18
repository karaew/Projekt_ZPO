//
// Created by konrad on 12.11.2026.
//

#include "../include/game_logic.hpp"



std::vector<int> GameLogic::PixelToBlock(int const pos_x, int const pos_y) const {
    int block_pos_x = pos_x/size_of_Block;
    int block_pos_y = pos_y/size_of_Block;
    return {block_pos_x, block_pos_y};
}

std::vector<std::vector<int>> GameLogic::BlockToPixel(int const pos_x, int const pos_y) const {
    std::vector<std::vector<int>> pixels(size_of_Block, std::vector<int>(2));
    pixels[0][0] = pos_x * 4;
    pixels[0][1] = pos_y * 4;
    pixels[1][0] = pos_x * 4 + 1;
    pixels[1][1] = pos_y * 4;
    pixels[2][0] = pos_x * 4;
    pixels[2][1] = pos_y * 4 - 1;
    pixels[3][0] = pos_x * 4 + 1;
    pixels[3][1] = pos_y * 4 - 1;
    return pixels;
}

void GameLogic::can_block_fall(const Figure &figure) {
    bool check = true;
    while (check) {
        for (const auto it : figure.blocks_) {
            if (board_[it.x_][it.y_ - 1] == 1) {
                check = false;
            }
        }
        for (const auto it : figure.blocks_) {
            it.alive_ = false;
            for (int it1 = 0; it1 < size_of_Block; it1++) {
                for (int it2 = 0; it2 < size_of_Block; it2++) {
                    const auto pixels = BlockToPixel(it.x_, it.y_);
                    board_[it.x_][it.y_] = 1;
                    window_[pixels[it1][0]][pixels[it1][1]].swap();
                }
            }
        }
    }
}