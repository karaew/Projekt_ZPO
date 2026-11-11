
#include "../include/siatka.hpp"


std::vector<std::vector<siatka>> okno(const int width, const int height) {
    std::vector<std::vector<siatka>> result(height, std::vector<siatka>(width, {false}));
    return result;
}