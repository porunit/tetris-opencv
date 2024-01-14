#pragma once

#include <vector>
#include "Figure.hpp"

//TODO ref
class Field {
public:
    std::vector<std::vector<int>> getField();
    void showField();
    void bindFigure(Figure *figure);
    void unbindFigure();
    void processStep();
    int removeFullLines();
    void clear();
    void checkUnderFigure();
    void transformFigure(); //Action?
    Field();
private:
    std::vector<std::vector<int>> field;
    int figureX, figureY;
    Figure *activeFigure = nullptr;
    void setFigureTiles();
    void removeFigureTiles();
};

std::ostream& operator<<(std::ostream& os, Field& f);