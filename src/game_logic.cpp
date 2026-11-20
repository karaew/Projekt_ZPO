//
// Created by konrad on 12.11.2026.
//

#include "../include/game_logic.hpp"

// funkcje zamieniajace wspolrzedne beda opierane na tym ze
// wspolrzedne (0,0) dla board znajduja sie na wspolrzednych (

int GameLogic::PixelToBlockX(int const pos_x) {
    const int block_pos_x = pos_x/size_of_Block;
    return block_pos_x;
}

int GameLogic::PixelToBlockY(int const pos_y) {
    const int block_pos_y = pos_y/size_of_Block;
    return block_pos_y;
}

int GameLogic::BlockToPixelX(int const pos_x, int const pointer) {
    const int side = static_cast<int>(sqrt(size_of_Block));
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_x = pointer % side;
    return pos_x * side + local_x + 24;
    // wartosc 24 dana na wzglad ze wzglad ze dla poczatku board_ (0, 0) na window_ jest to (20, 24)
}

int GameLogic::BlockToPixelY(int const pos_y, int const pointer) {
    const int side = static_cast<int>(sqrt(size_of_Block));
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_y = pointer % side;
    return pos_y * side + local_y + 20;
    // wartosc 24 dana na wzglad ze wzglad ze dla poczatku board_ (0, 0) na window_ jest to (20, 24)
}

void GameLogic::killPixels_from_Block(const Block &block) {
    for (int it = 0; it < size_of_Block; it++) {
        const int current_px_x = BlockToPixelX(block.x_, it);
        const int current_px_y = BlockToPixelY(block.y_, it);
        window_.set(current_px_x, current_px_y, false);
    }
}

void GameLogic::can_block_fall(int const time) {
    bool check = true;
    while (check) {
        for (const auto it : figure_.blocks_) {
            if ((window_.check(it.x_, it.y_ - 1) == 1 || it.y_ == 0)&& time == change_time) {
                check = false;
                break;
            }
        }
    }
    for (const auto it : figure_.blocks_) {
        it.alive_ = false;
        window_.set(it.x_, it.y_, true);
        killPixels_from_Block(it);
        new_figure();
        }
}

void GameLogic::can_block_move_R(const int input) {
    if (digitalRead(input) == LOW) {
        bool check = true;
        while (check) {
            for (const auto & block : figure_.blocks_) {
                if (window_.check(block.x_ + 1, block.y_) == true || block.x_ == 20) {
                    check = false;
                    break;
                }
            }
            figure_.move_R();
        }
    }
}
void GameLogic::can_block_move_L(const int input) {
    if (digitalRead(input) == LOW) {
        bool check = true;
        while (check) {
            for (const auto & block : figure_.blocks_) {
                if (window_.check(block.x_ - 1, block.y_) == true || block.x_ == 0) {
                    check = false;
                    break;
                }
            }
            figure_.move_L();
        }
    }
}