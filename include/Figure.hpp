#pragma once

#include "Color.hpp"

#include <vector>

struct Borders {
    int leftX;
    int rightX;
};

class Figure {
    Color color;
    std::vector<std::vector<bool>> map;
public:
    Figure(std::vector<std::vector<bool>> preset, Color p_color);
    std::vector<std::vector<bool>> getMap();
    void rotate();
    Color getColor();
    Borders getBorders();
};
