#include "gameManager.hpp"
#include "graphicManager.hpp"
#include "opencv2/opencv.hpp"
#include <functional>

#define enter 13
#define esc 27

void GameManager::processInput() {
    int leftDir = -1;
    int rightDir = 1;
    int buttonKey = cv::waitKey(LEVEL_ZERO_DELAY - LEVEL_INCREASE * getLevel());
    switch (buttonKey) {
        case 'a':
            field->moveFigureX(leftDir);
            break;
        case 'd':
            field->moveFigureX(rightDir);
            break;
        case 'r':
            field->transformFigure();
            break;
        case 32:
            field->skipFigure();
            break;
        case 27:
            std::exit(0);
        default:
            return;
    }
}

GameManager::GameManager() :
        field(new Field()),
        graphicManager(new GraphicManager()) {}

void GameManager::tick() {
    processInput();
    graphicManager->update(field->getField(), score, status);
    score += field->processStep();
    graphicManager->update(field->getField(), score, status);
}

void GameManager::start() {
    while (true) {
        score = 0;
        status = Status::GAME;
        gameCycle();
        status = Status::END;
        field->defeatScene();
        graphicManager->update(field->getField(), score, status);
        defeatSceneWait();
        field->clear();
    }
}

void GameManager::gameCycle() {
    graphicManager->init();
    while (true) {
        tick();
        if (field->isDefeat()) {
            break;
        }
    }
}

int GameManager::getLevel() const {
    int level = 0;
    if (score >= 100 && score < 1000) {
        level++;
    }
    if (score >= 1000) {
        level++;
    }
    return level;
}

void GameManager::defeatSceneWait() {
    int button;
    while (true) {
        button = cv::waitKey(100);
        if (button == enter) {
            break;
        }
        if (button == esc) {
            std::exit(0);
        }
    }
}



