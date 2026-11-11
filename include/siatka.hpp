//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_WINDOW_HPP
#define PROJEKT_ZPO_WINDOW_HPP


#include <vector>


#define Window_width 64
#define Window_height 128

struct siatka {
private:
    bool dostepne_;
public:
    siatka() : dostepne_(false) {}
    siatka(bool dostepne){dostepne_ = dostepne;}
};


std::vector<std::vector<siatka>> okno(const int width = Window_width, const int height = Window_height);



#endif //PROJEKT_ZPO_WINDOW_HPP