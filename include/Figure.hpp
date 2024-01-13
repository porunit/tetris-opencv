#pragma once

#include "Color.hpp"

#include <vector>

class Figure {
    Color color;
    std::vector<std::vector<bool>> map;
public:
    Figure();
    std::vector<std::vector<bool>> getMap();
    void rotate();
};
