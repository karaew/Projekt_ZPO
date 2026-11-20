//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_WINDOW_HPP
#define PROJEKT_ZPO_WINDOW_HPP


#define Window_width 64
#define Window_height 128

extern int size_of_Block;

class Pixel {
    bool occupied_;
public:
    Pixel() : occupied_(false), x_(0), y_(0) {};

    void swap() {occupied_ = !occupied_;}
    bool check() const {return occupied_;}
    int x_;
    int y_;
};

class Window {
    Pixel window_[Window_height][Window_width];

public:
    Window(int height = Window_height, int width = Window_width);

    Pixel* operator[](const int a) {return window_[a];}
    const Pixel* operator[](const int a) const {return window_[a];}

};

class GameBoard {
    bool board_[20][10]{};
    public:

    bool* operator[](const int a) { return board_[a]; }
    const bool* operator[](const int a) const { return board_[a]; }
};


#endif //PROJEKT_ZPO_WINDOW_HPP