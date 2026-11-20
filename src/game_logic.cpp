//
// Created by konrad on 12.11.2026.
//

#include "../include/game_logic.hpp"

int GameLogic::PixelToBlockX(int const pos_x) {
    const int block_pos_x = pos_x/size_of_Block;
    return block_pos_x;
}

int GameLogic::PixelToBlockY(int const pos_y) {
    const int block_pos_y = pos_y/size_of_Block;
    return block_pos_y;
}

int GameLogic::BlockToPixelX(int const pos_x, int const pointer) {
    switch (pointer) {
        case 0:
        case 2: return pos_x * size_of_Block;
        case 1:
        case 3: return pos_x * size_of_Block + 1;
        default: return -1;
    }
}
int GameLogic::BlockToPixelY(int const pos_y, int const pointer) {
    switch (pointer) {
        case 0:
        case 1: return pos_y * size_of_Block;
        case 2:
        case 3: return pos_y * size_of_Block - 1;
        default: return -1;
    }
}

void GameLogic::killPixels_from_Block(const Block &block) {
    for (int it = 0; it < size_of_Block; it++) {
        const int current_px_x = BlockToPixelX(block.x_, it);
        const int current_px_y = BlockToPixelY(block.y_, it);
        window_[current_px_x][current_px_y].swap();
    }
}

void GameLogic::can_block_fall(const Figure &figure, int const time) {
    bool check = true;
    while (check) {
        for (const auto it : figure.blocks_) {
            if ((board_[it.x_][it.y_ - 1] == 1 || it.y_ == 0)&& time == change_time) {
                check = false;
            }
        }
    }
    for (const auto it : figure.blocks_) {
        it.alive_ = false;
        board_[it.x_][it.y_] = true;
        killPixels_from_Block(it);
        new_figure();
        }
}
