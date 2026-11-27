#include "../include/block.hpp"



Block::Block(const int x, const int y, bool alive) {
    x_ = x;
    y_ = y;
    alive_ = alive;
}

void Block::fall() {
    y_ = y_ + 1;
}

Figure::Figure(const char typ_) : typ_(typ_){
    switch (typ_) {
        case 'I':
            blocks_[0] = Block(4, 0);
            blocks_[1] = Block(5, 0);
            blocks_[2] = Block(6, 0);
            blocks_[3] = Block(7, 0);
            break;
        case 'T':
            blocks_[0] = Block(4, 1);
            blocks_[1] = Block(5, 1);
            blocks_[2] = Block(6, 1);
            blocks_[3] = Block(5, 0);
            break;
        case 'J':
            blocks_[0] = Block(4, 0);
            blocks_[1] = Block(4, 1);
            blocks_[2] = Block(5, 1);
            blocks_[3] = Block(6, 1);
            break;
        case 'L':
            blocks_[0] = Block(4, 1);
            blocks_[1] = Block(5, 1);
            blocks_[2] = Block(6, 1);
            blocks_[3] = Block(6, 0);
            break;
        case 'O':
            blocks_[0] = Block(5, 0);
            blocks_[1] = Block(6, 0);
            blocks_[2] = Block(5, 1);
            blocks_[3] = Block(6, 1);
            break;
        case 's':
            blocks_[0] = Block(4, 1);
            blocks_[1] = Block(5, 1);
            blocks_[2] = Block(5, 0);
            blocks_[3] = Block(6, 0);
            break;
        case 'z':
            blocks_[0] = Block(4, 0);
            blocks_[1] = Block(5, 0);
            blocks_[2] = Block(5, 1);
            blocks_[3] = Block(6, 1);
            break;
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
                dx = -dy;
                dy = temp;
                block.x_ = blocks_[1].x_ + dx;
                block.y_ = blocks_[1].y_ + dy;
            }
        }
    }
}

void Figure::kill_blocks() {
    for (const auto &block : blocks_) {
        block.alive_ = false;
    }
}

void Figure::alive_blocks() {
    for (const auto &block : blocks_) {
        block.alive_ = true;
    }
}
