#include "GameManager.hpp"
#include "GraphicManager.hpp"
#include "opencv2/opencv.hpp"
#include <chrono>
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
    graphicManager->update(field->getField());
    setTimeout(10);
    field->processStep();
    graphicManager->update(field->getField());
    score += field->removeFullLines();
    graphicManager->update(field->getField());
}

void GameManager::start() {
    graphicManager->init();
    while (true) {
        tick();
    }
}


