#include "../include/figure.hpp"
#include "matrix.hpp"

#include <iostream>
#include <utility>

void Figure::rotate() {
    static Matrix rotationOperator({{0, -1},
                                    {1, 0}});

    auto newField = std::vector<std::vector<bool>>(map.size(), std::vector<bool>(DEFAULT_MATRIX_SIZE));
    for (int it = 0; it < map.size(); ++it) {
        for (int jt = 0; jt < map[it].size(); ++jt) {
            Matrix oldPos(1, 2);
            oldPos.getMatrixData()[0][0] = it - 2;
            oldPos.getMatrixData()[1][0] = jt - 2;
            Matrix newPos = rotationOperator * oldPos;
            newField[newPos.getMatrixData()[1][0] + 2][newPos.getMatrixData()[0][0] + 2] = map[jt][it];
        }
    }

    map = newField;
}

Figure::Figure(std::vector<std::vector<bool>> preset, Color p_color) :
        map(std::move(preset)),
        color(p_color) {}

std::vector<std::vector<bool>> Figure::getMap() {
    return map;
}

Color Figure::getColor() {
    return color;
}

Borders Figure::getBorders() {
    int maxX = 0;
    int minX = DEFAULT_MATRIX_SIZE - 1;
    for (int y = 0; y < DEFAULT_MATRIX_SIZE; ++y) {
        for (int x = 0; x < DEFAULT_MATRIX_SIZE; ++x) {
            if (!map[y][x]) {
                continue;
            }
            maxX = std::max(x, maxX);
            minX = std::min(x, minX);
        }
    }

    return Borders{
            minX,
            maxX
    };
}
