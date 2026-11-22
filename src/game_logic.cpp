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

int GameLogic::Block_To_PixelX(int const pos_x, int const pointer) {
    const int side = static_cast<int>(sqrt(size_of_Block));
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_x = pointer % side;
    return pos_x * side + local_x + 4;
    // wartosc 4 dana na wzglad ze wzglad ze dla poczatku board_ (0, 0) na window_ jest to (4, 20)
}

int GameLogic::Block_To_PixelY(int const pos_y, int const pointer) {
    const int side = static_cast<int>(sqrt(size_of_Block));
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_y = pointer / side;
    const int upside_y = 20 - pos_y;
    return upside_y * side + local_y + 2;
}

void GameLogic::set_Pixels_from_Block(const Block &block) {
    for (int it = 0; it < size_of_Block; it++) {
        const int current_px_x = Block_To_PixelX(block.x_, it);
        const int current_px_y = Block_To_PixelY(block.y_, it);
        window_.set(current_px_x, current_px_y, true);
    }
}

void GameLogic::can_block_fall(int const time) {
    if (time == change_time) {
        bool check = true;
        for (const auto it : figure_.blocks_) {
            if (window_.check(Block_To_PixelX(it.x_, 0), Block_To_PixelY(it.y_ - 1, 0)) == 1 || it.y_ == 0) {
                check = false;
                break;
            }
        }
        if (check) {
            for (auto &it : figure_.blocks_) {
                it.fall();
            }
        }
        else {
            for (auto &it : figure_.blocks_) {
                it.alive_ = false;
                set_Pixels_from_Block(it);
            }
            new_figure();
        }
    }
    refresh_window(*this);
}


bool GameLogic::can_block_move_R() {
    bool check = true;
    for (const auto &block : figure_.blocks_) {
        for (int it = 0; it < size_of_Block; it++) {
            if (window_.check(Block_To_PixelX(block.x_ + 1, it), Block_To_PixelY(block.y_, 0)) == true || block.x_ >= 9) {
                check = false;
                break;
            }
        }
    }
    if (check) {
        figure_.move_R();
    }
    return check;
}

bool GameLogic::can_block_move_L() {
    bool check = true;
    for (const auto & block : figure_.blocks_) {
        for (int it = 0; it < size_of_Block; it++) {
            if (window_.check(Block_To_PixelX(block.x_ - 1, 0), Block_To_PixelY(block.y_, 0)) == true || block.x_ <= 0) {
                check = false;
                break;
            }
        }
    }
    if (check) {
        figure_.move_L();
    }
    return check;
}


void refresh_window(const GameLogic &game) {
    u8g2.firstPage();
    do {
        constexpr int y_max = 44;
        // rozmieszczenie planszy (4, 2) - (22, 42)
        for (int y = 2; y < y_max; y++) {
            constexpr int x_max = 24;
            for (int x = 4; x < x_max; x++) {
                if (game.window_.check(x, y)) {
                    u8g2.setDrawColor(1);
                    u8g2.drawPixel(x, y);
                }
                else {
                    u8g2.setDrawColor(0);
                    u8g2.drawPixel(x, y);
                }
            }
        }
        for (const auto block : game.figure_.blocks_) {
            if (block.alive_ == true) {
                for (int it = 0; it < size_of_Block; it++) {
                    u8g2.setDrawColor(1);
                    u8g2.drawPixel(GameLogic::Block_To_PixelX(block.x_, it), GameLogic::Block_To_PixelY(block.y_, it));
                }
            }
        }
    }
    while (u8g2.nextPage());
}


void GameLogic::can_block_rotate() {
    int shift = 0;
    for (const auto &block : figure_.blocks_) {
        if (block.alive_ == true) {
            int dx = block.x_ - figure_.blocks_[1].x_;
            int dy = block.y_ - figure_.blocks_[1].y_;
            int const temp = dx;
            dx = dy;
            dy = temp;
            if  (figure_.blocks_[1].x_ + dx >= 10) {
                const int max = figure_.blocks_[1].x_ + dx - 10;
                if (max > shift){shift = max;};
            }
            if  (figure_.blocks_[1].x_ + dx < 0) {
                const int min = 0 + figure_.blocks_[1].x_ + dx;
                if (min < shift) {shift = min;}
            }
            if (window_.check(Block_To_PixelX(figure_.blocks_[1].x_ + dx, 0),
                              Block_To_PixelY(figure_.blocks_[1].y_ + dy, 0)) == true) {
                shift = -3;
                              }
        }
    }
    switch (shift) {
        case 0: figure_.rotate();
            break;
        case 1: figure_.move_L();
            figure_.rotate();
            break;
        case 2: figure_.move_L();
            figure_.move_L();
            figure_.rotate();
            break;
        case -1: figure_.move_R();
            figure_.rotate();
            break;
        case -2 :
            figure_.move_R();
            figure_.move_R();
            figure_.rotate();
        default : break;
    }
}