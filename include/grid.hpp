//
// Created by konrad on 4.11.2026.
//

#ifndef PROJEKT_ZPO_WINDOW_HPP
#define PROJEKT_ZPO_WINDOW_HPP


#define Window_width 128
#define Window_height 64
#include <stdint.h>


class Window {
    uint8_t window_[Window_height * Window_width / 8] = {};

public:
    static int byte_idx(const int x, const int y) {return y * Window_width / 8 + x / 8;}
    static int bit_idx(const int x, const int y) {return x % 8;}
    bool check(int x, int y) const;

    void set(int x, int y, bool value);
};



#endif //PROJEKT_ZPO_WINDOW_HPP