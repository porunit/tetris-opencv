#pragma once

#include <vector>
#include <map>
#include "Figure.hpp"


static const int DEFAULT_COORDINATES_VALUE = 0;
static const int EMPTY_FIELD = 0;
static const int FIELD_HEIGHT = 20;
static const int FIELD_WIDTH = 10;
static const int Y_DEFEAT_LINE = 1;
static const int DEFEAT_COLOR = -1;

//TODO ref delete friend class
class Field {
    friend class GameManager;

public:

    static int getFieldHeight();

    std::vector<std::vector<int>> *getField();

    void bindFigure(Figure *figure);

    void unbindFigure();

    int processStep();

    void clear();

    bool checkUnderFigure();

    void transformFigure();

    void skipFigure();

    void moveFigureX(int direction);

    Field();

    void defeatScene();

private:
    std::vector<std::vector<int>> *field;
    int figureX, figureY;
    Figure *activeFigure;
    std::map<int, Figure *> figurePresets;
    int presetCounter;

    int removeFullLines();

    void initFigurePresets();

    void setFigureTiles();

    void removeFigureTiles();

    void balanceField(int y);

    bool checkRightOrLeftFigure(int dir);

    bool checkTransformFigure();

    int getPresetCounter();

    bool isDefeat();
};

std::ostream &operator<<(std::ostream &os, Field &f);