#include "../include/block.hpp"


#include <stdexcept>

Block::Block(const int x, const int y, bool alive) {
    // 5 oraz 20 ustawiają bloczki na domyslnym
    // miejscu pojawiania sie bloczkow na planszy gry.
    x_ = x;
    y_ = y;
    alive_ = alive;
}

void Block::fall(const int time) {
    if (alive_) {
        if (time == 60 ) {
            y_ = y_ - 1;
        }
    }
}

Figure::Figure(const char typ_) : typ_(typ_){
    switch (typ_) {
        case 'I':
            blocks_ = {{4, 20}, {5, 20}, {6, 20}, {7, 20}};
            break;
        case 'T':
            blocks_ = {{4, 19}, {5, 19}, {6, 19}, {5, 20}};
            break;
        case 'J':
            blocks_ = {{4, 20}, {4, 19}, {5, 19}, {6, 19}};
            break;
        case 'L':
            blocks_ = {{4, 19}, {5, 19}, {6, 19}, {6, 20}};
            break;
        case 'O':
            blocks_ = {{5, 20}, {6, 20}, {5, 19}, {6, 19}};
            break;
        case 's':
            blocks_ = {{4, 19}, {5, 19}, {5, 20}, {6, 20}};
            break;
        case 'z':
            blocks_ = {{4, 20}, {5, 20}, {5, 19}, {6, 19}};
            break;
        default:
            throw std::invalid_argument("Invalid block type");
    }
}
void Figure::move_L() {

    for (auto &block : blocks_) {
        if (block.alive_) {
        block.x_ = block.x_ - 1;
        }
    }
};

void Figure::move_R() {
    for (auto &block : blocks_) {
        if (block.alive_) {
            block.x_ = block.x_ + 1;
        }
    }
};

void Figure::rotate() {
    for (auto &block : blocks_) {
        if (block.alive_) {
            if (typ_ != 'O') {
                int dx = block.x_ - blocks_[1].x_;
                int dy = block.y_ - blocks_[1].y_;
                int const temp = dx;
                dx = dy;
                dy = temp;
                block.x_ = blocks_[1].x_ + dx;
                block.y_ = blocks_[1].y_ + dy;
            }
        }
    }
}


