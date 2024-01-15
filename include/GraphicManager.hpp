#include "opencv2/opencv.hpp"
#include "Field.hpp"
#include "Status.hpp"
#include <vector>

#pragma once

static const int FIELD_ROWS = 1000;
static const int FIELD_COLS = 500;

static const int IMAGE_ROWS = 1000;
static const int IMAGE_COLS = 800;
static const int SCORE_COLS = IMAGE_COLS - FIELD_COLS;

static const int MEASURE = FIELD_ROWS / Field::getFieldHeight();

class GraphicManager {
    static cv::Scalar identifyColor(int codee);

    void clear();

    void draw(std::vector<std::vector<int>> field);

public:
    cv::Mat image;
    void init();

    void update(std::vector<std::vector<int>> *field, int score, Status status);
};
