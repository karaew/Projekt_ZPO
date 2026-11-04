
#include "../include/window.hpp"


std::vector<std::vector<px>> okno(const int width, const int height) {
    std::vector<std::vector<px>> result(height, std::vector<px>(width, {false}));
    return result;
}