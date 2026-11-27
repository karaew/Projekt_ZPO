//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_SIATKA_HPP
#define PROJEKT_ZPO_SIATKA_HPP

#define size_of_Block 16 // z ilu pikseli sklada sie block
#define size_of_Block_side 4
#define change_time 3

class Block {
public:
    int x_;
    int y_;
    mutable bool alive_;
    Block(int x = 0, int y = 0, bool alive = true);

    void fall();
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

    void kill_blocks();
    void alive_blocks();
};



#endif //PROJEKT_ZPO_SIATKA_HPP