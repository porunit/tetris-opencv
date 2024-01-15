#pragma once

#include "graphicManager.hpp"
#include "field.hpp"
#include "status.hpp"

const int LEVEL_ZERO_DELAY = 600;
const int LEVEL_INCREASE = 200;


class GameManager {
public:
    GameManager();

    void start();

private:
    GraphicManager *graphicManager;

    Field *field;

    int score;

    Status status;

    void tick();

    void gameCycle();

    void processInput();

    void defeatSceneWait();

    int getLevel() const;
};



