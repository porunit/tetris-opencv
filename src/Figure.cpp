#include "../include/Figure.hpp"
#include "matrix.hpp"

#include <iostream>

// FIXME magic number 12 (5)
const int DEFAULT_MATRIX_SIZE = 5;

void Figure::rotate() {
    static Matrix rotationOperator({{0, -1}, {1, 0}});

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
//    for (auto &it : newField) {
//        for (auto jt : it) {
//            std::cout << jt << " ";
//        }
//        std::cout << std::endl;
//    }

    map = newField;
}

//TODO
Figure::Figure() : map(std::vector<std::vector<bool>>(5, std::vector<bool>(DEFAULT_MATRIX_SIZE))) {
    color = Color::Green;
    map[0][2] = true;
    map[1][2] = true;
    map[2][2] = true;
    map[2][3] = true;
}

std::vector<std::vector<bool>> Figure::getMap() {
    return map;
}

Color Figure::getColor() {
    return color;
}
