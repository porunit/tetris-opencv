#include "GameManager.hpp"
#include "GraphicManager.hpp"
#include "opencv2/opencv.hpp"
#include <thread>
#include <functional>

void setTimeout(int milli) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
}

void GameManager::processInput() {
    int buttonKey = cv::waitKey(600 - 200 * getLevel());
    switch (buttonKey) {
        case 'a':
            field->moveFigureX(-1);
            break;
        case 'd':
            field->moveFigureX(1);
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

GameManager::GameManager() {
    field = new Field(),
            score = 0;
    graphicManager = new GraphicManager();
}

void GameManager::tick() {
    processInput();
    graphicManager->update(field->getField(), score, status);
    score += field->processStep();
    graphicManager->update(field->getField(), score, status);
}

//TODO ref
void GameManager::start() {
    while (true) {
        score = 0;
        status = Status::GAME;
        gameCycle();
        status = Status::END;
        field->defeatScene();
        graphicManager->update(field->getField(), score, status);
        int button = 0;
        while (true) {
            button = cv::waitKey(100);
            if (button == 13) {
                break;
            }
            if (button == 27) {
                std::exit(0);
            }
        }
        field->clear();
    }
}

bool GameManager::gameCycle() {
    graphicManager->init();
    while (true) {
        tick();
        if (!field->isDefeat()) {
            continue;
        }
        return false;
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



