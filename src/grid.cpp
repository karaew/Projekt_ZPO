
#include "../include/grid.hpp"



bool Window::check(const int x, const int y) const {
    if (x < 0 || y < 0) {return false;}
    return (window_[byte_idx(x, y)] & (1 << bit_idx(x, y))) != 0;
}

void Window::set(const int x, const int y, const bool value) {
    if (value == true){
        window_[byte_idx(x, y)] |= (1 << bit_idx(x, y));
    }
    else {window_[byte_idx(x, y)] &= ~(1 << bit_idx(x, y));}
}


