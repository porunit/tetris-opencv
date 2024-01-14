#include "Figure.hpp"
#include "Field.hpp"
#include <iostream>

static const int DEFAULT_COORDINATES_VALUE = 0;
static const int EMPTY_FIELD = 0;
static const int FIELD_HEIGHT = 20;
static const int FIELD_WIDTH = 10;

Field::Field() :
        field(std::vector<std::vector<int>>(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH))),
        figureX(DEFAULT_COORDINATES_VALUE),
        figureY(DEFAULT_COORDINATES_VALUE) {}

void Field::processStep() {
    if (activeFigure == nullptr) {
        bindFigure(new Figure());
        return;
    }
    removeFigureTiles();
    figureY++;
    setFigureTiles();
    if (figureY > 15) {
        unbindFigure();
    };
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
        //TODO fun to down all values higher this row
    }
    return scoreCounter;
}

void Field::showField() {
    for (auto &it: field) {
        for (auto jt: it) {
            std::cout << jt << " ";
        }
        std::cout << std::endl;
    }
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
