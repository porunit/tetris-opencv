#pragma once

#include "GraphicManager.hpp"
#include "Field.hpp"

enum Status {
    GAME,
    PAUSE,
    END
};

class GameManager {
public:
    GameManager();
    void start();
    void stop();
    void tick();
    void processInput();
private:
    GraphicManager *graphicManager;
    Field *field;
    int score;
    Status status;
};


