#include "Figure.hpp"
#include "Field.hpp"
#include <iostream>

static const int DEFAULT_COORDINATES_VALUE = 0;
static const int EMPTY_FIELD = 0;
static const int FIELD_HEIGHT = 20;
static const int FIELD_WIDTH = 10;

Field::Field() :
        field(std::vector<std::vector<int>>(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH))),
        activeFigure(nullptr),
        figureX(DEFAULT_COORDINATES_VALUE),
        figureY(DEFAULT_COORDINATES_VALUE) {}

void Field::processStep() {
    if (activeFigure == nullptr) {
        bindFigure(new Figure());
        return;
    }
    if (!checkUnderFigure()) {
        unbindFigure();
        bindFigure(new Figure());
        return;
    }
    removeFigureTiles();
    figureY++;
    setFigureTiles();
}

void Field::bindFigure(Figure *figure) {
    figureY = -2;
    figureX = 3;
    activeFigure = figure;
}

void Field::unbindFigure() {
    delete activeFigure;
    activeFigure = nullptr;
}

//TODO ref
void Field::setFigureTiles() {
    for (int it = 0; it < activeFigure->getMap().size(); ++it) {
        if (figureY + it < 0 || figureY + it >= FIELD_HEIGHT) {
            continue;
        }
        for (int jt = 0; jt < activeFigure->getMap()[it].size(); ++jt) {
            if (figureX + jt < 0 || figureX + jt >= FIELD_WIDTH) {
                continue;
            }
            if (!activeFigure->getMap()[it][jt]) {
                continue;
            }
            int tileX = figureX + jt;
            int tileY = figureY + it;
            field[tileY][tileX] = activeFigure->getColor();
        }
    }
}

void Field::removeFigureTiles() {
    for (int it = 0; it < activeFigure->getMap().size(); ++it) {
        if (figureY + it < 0 || figureY + it >= FIELD_HEIGHT) {
            continue;
        }
        for (int jt = 0; jt < activeFigure->getMap()[it].size(); ++jt) {
            if (figureX + jt < 0 || figureX + jt >= FIELD_WIDTH) {
                continue;
            }
            if (!activeFigure->getMap()[it][jt]) {
                continue;
            }
            int tileX = figureX + jt;
            int tileY = figureY + it;
            field[tileY][tileX] = EMPTY_FIELD;
        }
    }
}

std::vector<std::vector<int>> Field::getField() {
    return field;
}

//TODO checks
void Field::transformFigure() {
    removeFigureTiles();

    activeFigure->rotate();
    if (!checkTransformFigure()) {
        activeFigure->rotate();
        activeFigure->rotate();
        activeFigure->rotate();
    }

    setFigureTiles();
}

bool Field::checkTransformFigure() {
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (!activeFigure->getMap()[y][x]) {
                continue;
            }
            int globalY = y + figureY;
            int globalX = x + figureX;
            if (globalY > FIELD_HEIGHT - 1 || globalX < 0 || globalX > FIELD_WIDTH - 1) {
                return false;
            }
            if (field[globalY][globalX] != EMPTY_FIELD) {
                return false;
            }
        }
    }
    return true;
}

//TODO ref
bool Field::checkUnderFigure() {
    bool isBottomFound = false;
    for (int y = 4; y > 0; --y) {
        for (int x = 0; x < 5; x++) {
            if (!activeFigure->getMap()[y][x]) {
                continue;
            }
            isBottomFound = true;
            int globalY = y + figureY;
            int globalX = x + figureX;
            int expectedY = globalY + 1;
            if (expectedY > FIELD_HEIGHT - 1 || field[expectedY][globalX] != EMPTY_FIELD) {
                return false;
            }
        }
        if (isBottomFound) {
            break;
        }
    }
    return true;
}

void Field::balanceField(int y) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
        field[y][j] = 0;
    }
    for (int curY = y; curY > 0; --curY) {
        for (int curX = 0; curX < FIELD_WIDTH; ++curX) {
            field[curY][curX] = field[curY - 1][curX];
            field[curY - 1][curX] = 0;
        }
    }
}

int Field::removeFullLines() {
    int scoreCounter = 0;
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        int lineScoreCounter = 0;
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (field[i][j] != 0) {
                lineScoreCounter++;
            }
        }
        if (lineScoreCounter != FIELD_WIDTH) {
            continue;
        }
        scoreCounter += lineScoreCounter * 4;
        balanceField(i);
    }
    return scoreCounter;
}

void Field::moveFigureX(int direction) {
    Borders borders = activeFigure->getBorders();
    if (borders.leftX + figureX + direction < 0 ||
        borders.rightX + figureX + direction > FIELD_WIDTH - 1) {
        return;
    }
    removeFigureTiles();
    figureX += direction;
    setFigureTiles();
}

void Field::skipFigure() {
    removeFigureTiles();
    while (checkUnderFigure()) {
        figureY++;
    }
    setFigureTiles();
}

std::ostream &operator<<(std::ostream &os, Field &f) {
    for (auto &it: f.getField()) {
        for (auto jt: it) {
            os << jt << " ";
        }
        os << std::endl;
    }
    return os;
}
