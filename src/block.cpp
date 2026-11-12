#include "../include/block.hpp"


#include <stdexcept>

Block::Block(const int x, const int y, bool alive) {
    x_ = 5 + x;
    y_ = 20 + y;
    alive_ = alive;
}

void Block::fall(const int time) {
    if (alive_) {
        if (time == 60 ) {
            y_ = y_ - 1;
        }
    }
}

figure::figure(char typ) : typ_(typ){
    switch (typ) {
        case 'I':
            blocks_ = {{-1, 0}, {0, 0}, {1, 0}, {2, 0}};
        case 'T':
            blocks_ = {{-1, -1}, {0, -1}, {1, -1}, {0, 0}};
        case 'J':
            blocks_ = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
        case 'L':
            blocks_ = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}};
        case 'O':
            blocks_ = {{0, 0}, {1, 0}, {0, -1}, {1, -1}};
        case 's':
            blocks_ = {{-1, -1}, {0, -1}, {0, 0}, {1, 0}};
        case 'z':
            blocks_ = {{-1, 0}, {0, 0}, {0, -1}, {1, -1}};
        default:
            throw std::invalid_argument("Invalid block type");
    }
}
void figure::move_L() {

    for (auto &block : blocks_) {
        if (block.alive_) {
        block.x_ = block.x_ - 1;
        }
    }
};

void figure::move_R() {
    for (auto &block : blocks_) {
        if (block.alive_) {
            block.x_ = block.x_ + 1;
        }
    }
};

void figure::rotate() {
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


