//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_SIATKA_HPP
#define PROJEKT_ZPO_SIATKA_HPP
#include <vector>
#include <string>
#include <stdexcept>

class Block {
public:
    int x_;
    int y_;
    bool alive_;
    Block(int x, int y, bool alive = true);

    void fall(int time);
    ~Block() = default;
};

class figure {
    public:
    char typ_;
    std::vector <Block> blocks_;
    std::vector<std::vector<Block>> state;

    figure(char typ_);
    void move_L();
    void move_R();
    void rotate();

};




#endif //PROJEKT_ZPO_SIATKA_HPP