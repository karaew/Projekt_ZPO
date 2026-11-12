//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_WINDOW_HPP
#define PROJEKT_ZPO_WINDOW_HPP


#include <vector>


#define Window_width 64
#define Window_height 128

class Pixel {
    bool occupied_;
public:
    Pixel() : occupied_(false), x_(0), y_(0) {};

    void zamien() {occupied_ = !occupied_;}
    int x_;
    int y_;
};

class Window {
    public:
    std::vector<std::vector<Pixel>> window_;

    Window(int heigt = Window_height, int width = Window_width);
};



#endif //PROJEKT_ZPO_WINDOW_HPP