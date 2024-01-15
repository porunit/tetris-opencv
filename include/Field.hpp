#pragma once

#include <vector>
#include <map>
#include "Figure.hpp"


static const int DEFAULT_COORDINATES_VALUE = 0;
static const int EMPTY_FIELD = 0;
static const int FIELD_HEIGHT = 20;
static const int FIELD_WIDTH = 10;


//TODO ref
class Field {
    friend class GameManager;

public:

    static int getFieldHeight();

    std::vector<std::vector<int>> *getField();

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
    std::map<int, Figure*> figurePresets;
    int presetCounter;

    void initFigurePresets();
    void setFigureTiles();

    void removeFigureTiles();

    void balanceField(int y);

    bool checkRightOrLeftFigure(int dir);

    bool checkTransformFigure();
    int getPresetCounter();
};

std::ostream &operator<<(std::ostream &os, Field &f);