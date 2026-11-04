//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_WINDOW_HPP
#define PROJEKT_ZPO_WINDOW_HPP


#include <vector>


#define Window_width 64
#define Window_height 128

struct px {

    bool dostepne_;
    px() : dostepne_(false) {}
    px(bool dostepne){dostepne_ = dostepne;}
};


std::vector<std::vector<px>> okno(const int width = Window_width, const int height = Window_height);
#endif //PROJEKT_ZPO_WINDOW_HPP