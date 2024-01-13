#pragma once

#include <vector>
#include "Figure.hpp"

class Field {
public:
    void bindFigure(Figure &figure);
    void unbindFigure();
    void processStep();
    int removeFullLines();
    void clear();
    void transformFigure(); //Action?
    void setFigureTiles();
    void removeFigureTiles();

private:
    std::vector<std::vector<int>> field;
    int figureX, figureY;
    Figure &activeFigure;
    bool isFigureDown;

};
