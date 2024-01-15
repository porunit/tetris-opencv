#pragma once

#include "GraphicManager.hpp"
#include "Field.hpp"
#include "Status.hpp"

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



