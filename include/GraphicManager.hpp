#include "opencv2/opencv.hpp"
#include "Field.hpp"
#include <vector>

#pragma once

static const int ROWS = 1000;
static const int COLS = 500;
static const int MEASURE = ROWS / Field::getFieldHeight();

class GraphicManager {
    static cv::Scalar identifyColor(int codee);

    void clear();

    void draw(std::vector<std::vector<int>> field);

public:
    cv::Mat image = cv::Mat::zeros(ROWS, COLS, CV_8UC3);
    void init() const;
    void update(std::vector<std::vector<int>> *field);
};
