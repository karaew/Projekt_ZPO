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

int GameLogic::Block_To_PixelX(int const pos_x, int const pointer) {
    const int side = static_cast<int>(sqrt(size_of_Block));
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_x = pointer % side;
    return pos_x * side + local_x + 4;
}

int GameLogic::Block_To_PixelY(int const pos_y, int const pointer) {
    const int side = static_cast<int>(sqrt(size_of_Block));
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_y = pointer / side;
    return pos_y * side + local_y + 1;
}

void GameLogic::set_Pixels_from_Block(const Block &block) {
    window_.set(block.x_, block.y_, true);
}

void clear_lane(GameLogic &game) {
    for (int y = 0; y < Game_Window_height; y++) {
        int check = 0;
        for (int x = 0; x < Game_Window_width; x++) {
            if (game.window_.check(x, y) == true) {
                check++;
            }
        }
        if (check == Game_Window_width) {
            for (int y_idx = y; y_idx > 0; y_idx--) {
                for (int x = 0; x < Game_Window_width; x++) {
                    const bool upper_val = game.window_.check(x, y_idx - 1);
                    game.window_.set(x, y_idx, upper_val);
                }
            }
            for (int x = 0; x < Game_Window_width; x++) {
                game.window_.set(x, 0, false);
            }
        }
    }
}

void GameLogic::can_block_fall(int const time) {
    if (time == change_time) {
        bool check = true;
        for (const auto it : figure_.blocks_) {
            if (it.y_ == 19 || window_.check(it.x_, it.y_ + 1) == true ) {
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
            clear_lane(*this);
            new_figure();
        }
    }
    refresh_window(*this);
}


bool GameLogic::can_block_move_R() {
    bool check = true;
    for (const auto &block : figure_.blocks_) {
        if (window_.check(block.x_ + 1, block.y_) == true || block.x_ >= 9) {
            check = false;
            break;
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
        if (window_.check(block.x_ - 1, block.y_) == true || block.x_ <= 0) {
            check = false;
            break;
        }
    }
    if (check) {
        figure_.move_L();
    }
    return check;
}


void GameLogic::can_block_rotate() {
    int shift = 0;
    for (const auto &block : figure_.blocks_) {
        if (block.alive_ == true) {
            int dx = block.x_ - figure_.blocks_[1].x_;
            int dy = block.y_ - figure_.blocks_[1].y_;
            int const temp = dx;
            dx = -dy;
            dy = temp;
            if  (figure_.blocks_[1].x_ + dx >= 10) {
                const int max = figure_.blocks_[1].x_ + dx - 9;
                if (max > shift){shift = max;};
            }
            if  (figure_.blocks_[1].x_ + dx < 0) {
                const int min = 0 + figure_.blocks_[1].x_ + dx;
                if (min < shift) {shift = min;}
            }
            if (window_.check(figure_.blocks_[1].x_ + dx, figure_.blocks_[1].y_ + dy) == true) {
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


void refresh_window(GameLogic &game) {
    u8g2.firstPage();
    do {
        for (int y = 0; y < Game_Window_height; y++) {
            for (int x = 0; x < Game_Window_width; x++) {
                if (game.window_.check(x, y) == true) {
                    u8g2.setDrawColor(1);
                    u8g2.drawBox(GameLogic::Block_To_PixelX(x, 0), GameLogic::Block_To_PixelY(y, 0),
                                 static_cast<int>(sqrt(size_of_Block)), static_cast<int>(sqrt(size_of_Block)));
                }
            }
        }
        for (const auto block : game.figure_.blocks_) {
            if (block.alive_ == true) {
                u8g2.setDrawColor(1);
                u8g2.drawBox(GameLogic::Block_To_PixelX(block.x_, 0), GameLogic::Block_To_PixelY(block.y_, 0), static_cast<int>(sqrt(size_of_Block)), static_cast<int>(sqrt(size_of_Block)));
            }
        }
    }
    while (u8g2.nextPage());

}


