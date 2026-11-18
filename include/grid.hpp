//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_WINDOW_HPP
#define PROJEKT_ZPO_WINDOW_HPP


#include <vector>


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
    std::vector<std::vector<Pixel>> window_;
public:
    Window(int height = Window_height, int width = Window_width);

    std::vector<Pixel>& operator[](const int a) {return window_[a];}
    const std::vector<Pixel>& operator[](const int a) const {return window_[a];}

};

class GameBoard {
    std::vector<std::vector<int>> board_;
    public:
    GameBoard(int height = 20, int width = 10) : board_(height, std::vector<int>(width, 0)) {};

    std::vector<int>& operator[](const int a) {return board_[a];}
    const std::vector<int>& operator[](const int a) const {return board_[a];}

};


#endif //PROJEKT_ZPO_WINDOW_HPP