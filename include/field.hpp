#pragma once

#include <vector>
#include <map>
#include "figure.hpp"


static const int DEFAULT_COORDINATES_VALUE = 0;
static const int EMPTY_FIELD = 0;
static const int FIELD_HEIGHT = 20;
static const int FIELD_WIDTH = 10;
static const int Y_DEFEAT_LINE = 1;
static const int DEFEAT_COLOR = -1;
static const int Y_OFFSET = -2;
static const int X_OFFSET = 3;

class Field {

public:

    static int getFieldHeight();

    std::vector<std::vector<int>> *getField();

    int processStep();

    void clear();

    void transformFigure();

    void skipFigure();

    void moveFigureX(int direction);

    Field();

    void defeatScene();

    bool isDefeat();

private:
    std::vector<std::vector<int>> *field;
    std::map<int, Figure *> figurePresets;
    Figure *activeFigure;
    int figureX, figureY;
    int presetCounter;

    int removeFullLines();

    void initFigurePresets();

    void unbindFigure();

    void bindFigure(Figure *figure);

    bool checkUnderFigure();

    void setFigureTiles();

    void removeFigureTiles();

    void balanceField(int y);

    bool checkRightOrLeftFigure(int dir);

    bool checkTransformFigure();

    int getPresetCounter();
};

std::ostream &operator<<(std::ostream &os, Field &f);