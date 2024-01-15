#include "GameManager.hpp"
#include "GraphicManager.hpp"
#include "opencv2/opencv.hpp"
#include <thread>
#include <functional>

void GameManager::processInput() {
    int buttonKey = cv::waitKey(350);
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
        default:
            return;
    }

}

GameManager::GameManager() {
    field = new Field(),
            score = 0;
    status = Status::GAME;
    graphicManager = new GraphicManager();
}

void setTimeout(int milli) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
}

void GameManager::tick() {
    processInput();
    graphicManager->update(field->getField(), score, status);
    field->processStep();
    graphicManager->update(field->getField(), score, status);
    score += field->removeFullLines();
    graphicManager->update(field->getField(), score, status);
}

//TODO 2 cicla for restart
void GameManager::start() {
    graphicManager->init();
    while (true) {
        tick();
        if (!field->isDefeat()) {
            continue;
        }
        status = Status::END;
        field->defeatScene();
        graphicManager->update(field->getField(), score, status);
        setTimeout(100);
        cv::waitKey(100000);
        break;
    }
}



