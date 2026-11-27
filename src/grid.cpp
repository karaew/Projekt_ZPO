
#include "../include/grid.hpp"



bool Window::check(const int x, const int y) const {
    if (x < 0 || x >= Game_Window_width || y < 0 || y >= Game_Window_height) {
        return false;
    }
    const int x_real = y;
    const int y_real = (Game_Window_width - 1) - x;

    return (window_[byte_idx(x_real, y_real)] & (1 << bit_idx(x_real, y_real))) != 0;
}

void Window::set(const int x, const int y, const bool value) {
    if (x < 0 || x >= Game_Window_width || y < 0 || y >= Game_Window_height) {
        return;
    }
    const int x_real = y;
    const int y_real = (Game_Window_width - 1) - x;

    if (value) {
        window_[byte_idx(x_real, y_real)] |= (1 << bit_idx(x_real, y_real));
    } else {
        window_[byte_idx(x_real, y_real)] &= ~(1 << bit_idx(x_real, y_real));
    }
}
