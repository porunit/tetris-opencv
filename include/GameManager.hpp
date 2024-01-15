#pragma once

#include "GraphicManager.hpp"
#include "Field.hpp"
#include "Status.hpp"

class GameManager {
public:
    GameManager();
    void start();
    void tick();
    void processInput();
    bool gameCycle();
private:
    GraphicManager *graphicManager;
    Field *field;
    int score;
    Status status;
};


