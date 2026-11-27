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
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_x = pointer % size_of_Block_side;
    // wartosc po local_x odpowiada za umieszczenie planszy na ekranie,
    // '+' przesuwa w prawo, '-' w lewo
    return pos_x * size_of_Block_side + local_x + 4;
}

int GameLogic::Block_To_PixelY(int const pos_y, int const pointer) {
    if (pointer < 0 || pointer >= size_of_Block) {
        return -1;
    }
    const int local_y = pointer / size_of_Block_side;
    return pos_y * size_of_Block_side + local_y + 4;
    // wartosc po local_y odpowiada za umieszczenie planszy na ekranie,
    // '+' przesuwa w dol, '-' w gore
}

void GameLogic::set_Pixels_from_Block(const Block &block) {
    window_.set(block.x_, block.y_, true);
}

void GameLogic::display_next_figure() {
    for (const auto &it : next_figure_.blocks_) {
        const int pos_x = GameLogic::Block_To_PixelX(it.x_, 0) + 28;
        const int pos_y = GameLogic::Block_To_PixelY(it.y_, 0);
        u8g2.setDrawColor(1);
        u8g2.drawBox(pos_x, pos_y, size_of_Block_side, size_of_Block_side);
        u8g2.setDrawColor(0);
        u8g2.drawBox(pos_x + 1, pos_y + 1, size_of_Block_side - 2, size_of_Block_side - 2);
    }
}

void GameLogic::new_figure() {
    figure_ = next_figure_;
    figure_.alive_blocks();
    next_figure_ = Figure(types[random(0,7)]);
    next_figure_.kill_blocks();
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
        if (window_.check(block.x_ - 1, block.y_) == true || block.x_ >= 9) {
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
        if (window_.check(block.x_ + 1, block.y_) == true || block.x_ <= 0) {
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
            if  (figure_.blocks_[1].x_ + dx >= 9) {
                const int max = figure_.blocks_[1].x_ + dx - 9;
                if (max > shift){shift = max;};
            }
            if  (figure_.blocks_[1].x_ + dx <= 0) {
                const int min = 0 + figure_.blocks_[1].x_ + dx;
                if (min < shift) {shift = min;}
            }
            if (window_.check(figure_.blocks_[1].x_ + dx, figure_.blocks_[1].y_ + dy) == true) {
                shift = -3;
            }
            if (figure_.blocks_[1].y_ + dy >= 19 || figure_.blocks_[1].y_ + dy <= 0) {shift = -3;}
        }
    }
    switch (shift) {
        case 0: {
            figure_.rotate();
            break;
        }
        case 1: {
            const bool check = can_block_move_L();
            if (check){figure_.rotate();}
            break;
        }
        case 2: {
            const bool check_1 = can_block_move_L();
            if (check_1) {
                const bool check_2 = can_block_move_L();
                if (check_2){ figure_.rotate();}
                else {figure_.move_R();}
            }
                break;
        }
        case -1: {
            const bool check = can_block_move_R();
            if (check) {
                figure_.rotate();
                break;
            }
        }
        case -2: {
            const bool check_1 = can_block_move_R();
            if (check_1) {
                const bool check_2 = can_block_move_R();
                if (check_2){ figure_.rotate();}
                else {figure_.move_L();}
            }
            break;
        }
        default : break;
    }
}



void draw_frame() {
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, Window_width, Window_height);
    u8g2.setDrawColor(0);
    u8g2.drawBox(size_of_Block_side, size_of_Block_side,
                 Window_width - 2 * size_of_Block_side,
                 Window_height - 2 * size_of_Block_side);
    //rysowanie ramki dla calego ekranu

    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0,(Game_Window_width + 2) * size_of_Block_side,
        (Game_Window_height + 2)  * size_of_Block_side);
    u8g2.setDrawColor(0);
    u8g2.drawBox(size_of_Block_side, size_of_Block_side,
        Game_Window_width * size_of_Block_side,
        Game_Window_height * size_of_Block_side);
    // rysowanie ramki dla planszy gry
}


void refresh_window(GameLogic &game) {
    u8g2.clearBuffer();
    draw_frame();
    for (int y = 0; y < Game_Window_height; y++) {
        for (int x = 0; x < Game_Window_width; x++) {
            if (game.window_.check(x, y) == true) {
                u8g2.setDrawColor(1);
                u8g2.drawBox(GameLogic::Block_To_PixelX(x, 0), GameLogic::Block_To_PixelY(y, 0), size_of_Block_side, size_of_Block_side);
                u8g2.setDrawColor(0);
                u8g2.drawBox(GameLogic::Block_To_PixelX(x, size_of_Block_side + 1), GameLogic::Block_To_PixelY(y, size_of_Block_side + 1),
                    size_of_Block_side - 2, size_of_Block_side - 2);
            }
        }
    }
    for (const auto block : game.figure_.blocks_) {
        if (block.alive_ == true) {
            u8g2.setDrawColor(1);
            u8g2.drawBox(GameLogic::Block_To_PixelX(block.x_, 0), GameLogic::Block_To_PixelY(block.y_, 0), size_of_Block_side, size_of_Block_side);
            u8g2.setDrawColor(0);
            u8g2.drawBox(GameLogic::Block_To_PixelX(block.x_, size_of_Block_side + 1), GameLogic::Block_To_PixelY(block.y_, size_of_Block_side + 1),
                size_of_Block_side - 2, size_of_Block_side - 2);
        }
    }
    game.display_next_figure();
    u8g2.sendBuffer();
}

