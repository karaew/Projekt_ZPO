//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_SIATKA_HPP
#define PROJEKT_ZPO_SIATKA_HPP

#define size_of_Block 4
#define change_time 60

class Block {
public:
    int x_;
    int y_;
    mutable bool alive_;
    Block(int x = 0, int y = 0, bool alive = true);

    void fall(int time);
    ~Block() = default;
};

class Figure {
    public:
    char typ_;
    Block blocks_[4];

    explicit Figure(char typ_);

    void move_L();
    void move_R();
    void rotate();
};



#endif //PROJEKT_ZPO_SIATKA_HPP