#include "Figure.hpp"
#include "Field.hpp"
#include <iostream>

#define l_carcase {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,0,0}}
#define i_carcase {{0,0,0,0,0},{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0},{0,0,0,0,0}}
#define c_carcase {{0,0,0,0,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,0,0,0},{0,0,0,0,0}}
#define t_carcase {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,0,0,0,0},{0,0,0,0,0}}
#define j_carcase {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,1,0},{0,0,0,0,0}}
#define rj_carcase {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,1,0,0,0},{0,0,0,0,0}}

Field::Field() :
        field(std::vector<std::vector<int>>(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH))),
        activeFigure(nullptr),
        figureX(DEFAULT_COORDINATES_VALUE),
        figureY(DEFAULT_COORDINATES_VALUE) {
    initFigurePresets();
    presetCounter = 0;
}

void Field::processStep() {

    if (activeFigure == nullptr) {
        bindFigure(figurePresets[getPresetCounter()]);
        return;
    }
    removeFigureTiles();
    if (!checkUnderFigure()) {
        setFigureTiles();
        unbindFigure();
        bindFigure(figurePresets[getPresetCounter()]);
        return;
    }
    figureY++;
    setFigureTiles();
}

void Field::bindFigure(Figure *figure) {
    figureY = -2;
    figureX = 3;
    activeFigure = figure;
}

void Field::unbindFigure() {
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

std::vector<std::vector<int>> *Field::getField() {
    return &field;
}

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

    for (int y = 4; y > 0; --y) {
        for (int x = 0; x < 5; x++) {
            if (!activeFigure->getMap()[y][x]) {
                continue;
            }
            int globalY = y + figureY;
            int globalX = x + figureX;
            int expectedY = globalY + 1;
            if (expectedY > FIELD_HEIGHT - 1) {
                return false;
            }
            if (field[expectedY][globalX] != EMPTY_FIELD) {
                return false;
            }
        }
    }
    return true;
}


//TODO ref with moveFigure
bool Field::checkRightOrLeftFigure(int dir) {
    for (int y = 4; y >= 0; --y) {
        for (int x = 0; x < 5; x++) {
            if (!activeFigure->getMap()[y][x]) {
                continue;
            }
            int globalY = y + figureY;
            int globalX = x + figureX;
            int expectedX = globalX + dir;
            if (expectedX > FIELD_WIDTH - 1 || expectedX < 0 || globalY < 0) {
                return false;
            }
            if (field[globalY][expectedX] != EMPTY_FIELD) {
                return false;
            }
        }
    }
    return true;
}

void Field::balanceField(int y) {
    // Очищаем текущий ряд
    for (int j = 0; j < FIELD_WIDTH; ++j) {
        field[y][j] = 0;
    }

    // Сдвигаем строки вниз, начиная с текущего ряда
    for (int curY = y; curY > 0; --curY) {
        for (int curX = 0; curX < FIELD_WIDTH; ++curX) {
            field[curY][curX] = field[curY - 1][curX];
        }
    }

    // Очищаем верхний ряд
    for (int j = 0; j < FIELD_WIDTH; ++j) {
        field[0][j] = 0;
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
        if (lineScoreCounter == FIELD_WIDTH) {
            scoreCounter += lineScoreCounter * 4;
            balanceField(i);
        }
    }
    return scoreCounter;
}


void Field::moveFigureX(int direction) {
    removeFigureTiles();
    Borders borders = activeFigure->getBorders();
    if (borders.leftX + figureX + direction < 0 ||
        borders.rightX + figureX + direction > FIELD_WIDTH - 1 ||
        !checkRightOrLeftFigure(direction)) {
        setFigureTiles();
        return;
    }
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

int Field::getFieldHeight() {
    return FIELD_HEIGHT;
}

void Field::initFigurePresets() {
    std::vector<std::vector<bool>> l_preset = {l_carcase};
    std::vector<std::vector<bool>> i_preset = {i_carcase};
    std::vector<std::vector<bool>> c_preset = {c_carcase};
    std::vector<std::vector<bool>> t_preset = {t_carcase};
    std::vector<std::vector<bool>> j_preset = {j_carcase};
    std::vector<std::vector<bool>> rj_preset = {rj_carcase};

    figurePresets[0] = new Figure(l_preset, Color::Green);
    figurePresets[1] = new Figure(i_preset, Color::Blue);
    figurePresets[2] = new Figure(c_preset, Color::ORANGE);
    figurePresets[3] = new Figure(t_preset, Color::RED);
    figurePresets[4] = new Figure(j_preset, Color::Yellow);
    figurePresets[5] = new Figure(rj_preset, Color::Yellow);
}

int Field::getPresetCounter() {
    presetCounter = presetCounter > 5 ? 0 : presetCounter;
    return presetCounter++;
}

std::ostream &operator<<(std::ostream &os, Field &f) {
    for (auto &it: *f.getField()) {
        for (auto jt: it) {
            os << jt << " ";
        }
        os << std::endl;
    }
    return os;
}


