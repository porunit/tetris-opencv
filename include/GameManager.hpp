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
    void start();
    void stop();
    void tick();
    void processInput();

private:
    static GraphicManager graphicManager;
    Field field;
    Status status;

};


