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
    bool checkUnderFigure();
    void transformFigure();
    void skipFigure();
    void moveFigureX(int direction);
    Field();
private:
    std::vector<std::vector<int>> field;
    int figureX, figureY;
    Figure *activeFigure;
    void setFigureTiles();
    void removeFigureTiles();
    void balanceField(int y);

    bool checkTransformFigure();
};

std::ostream& operator<<(std::ostream& os, Field& f);