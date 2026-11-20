
#include "../include/grid.hpp"

Window::Window(const int height, const int width) {
    int y = Window_height;
    for (int i = 0; y < height; i++) {
        int x = 0;
        for (int j = 0 ; j < width; j++) {
            window_[i][j].x_ = x;
            window_[i][j].y_ = y;
            x++;
        }
        y--;
    }
};


