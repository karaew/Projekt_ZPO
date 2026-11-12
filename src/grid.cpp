
#include "../include/grid.hpp"

Window::Window(int height, int width) {
    std::vector<std::vector<Pixel>> result(height, std::vector<Pixel>(width));
    int y = Window_height;
    for (auto &row : result) {
        int x = 0;
        for (auto &col : row) {
            col.x_ = x;
            col.y_ = y;
            x++;
        }
        y--;
    }
    window_ = result;
};
