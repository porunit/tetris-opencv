#include "opencv2/opencv.hpp"
#include "field.hpp"
#include "status.hpp"
#include <vector>

#pragma once

static const int FIELD_ROWS = 1000;
static const int FIELD_COLS = 500;

static const int IMAGE_ROWS = 1000;
static const int IMAGE_COLS = 800;
static const int SCORE_COLS = IMAGE_COLS - FIELD_COLS;
static const int CUBE_THICKNESS = 4;
static const char *WINDOW_NAME = "TetrisCV";
static const int MEASURE = FIELD_ROWS / Field::getFieldHeight();

class GraphicManager {
    cv::Mat image;

    void drawField(std::vector<std::vector<int>> field);

    void drawDefeatScreen();

    void drawControls();

    void drawMenu(int score);

    static cv::Scalar identifyColor(int codee);

    void clear();

    static int calculateScoreX(int score);

    int calcLevel(int score);

public:

    void init();

    void update(std::vector<std::vector<int>> *field, int score, Status status);
};
