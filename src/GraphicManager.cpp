#include "GraphicManager.hpp"

void GraphicManager::draw(std::vector<std::vector<int>> field) {
    for (int y = 0; y < field.size(); ++y) {
        for (int x = 0; x < field[0].size(); ++x) {
            if (field[y][x] == 0) {
                continue;
            }
            int color = field[y][x];
            int leftCornerX = MEASURE * x;
            int leftCornerY = MEASURE * y;
            cv::rectangle(
                    GraphicManager::image,
                    cv::Point(leftCornerX, leftCornerY),
                    cv::Point(leftCornerX + MEASURE, leftCornerY + MEASURE),
                    identifyColor(color),
                    2
            );
        }
    }
}

cv::Scalar GraphicManager::identifyColor(int code) {
    switch (code) {
        case 1:
            return {255, 255, 0};
        case 2:
            return {0, 255, 0};
        case 3:
            return {30, 144, 255};
        case 4:
            return {255, 0, 0};
        default:
            return {255, 255, 255};
    }
}

void GraphicManager::clear() {
    image = cv::Mat::zeros(ROWS, COLS, CV_8UC3);
}

void GraphicManager::update(std::vector<std::vector<int>> *field) {
    clear();
    draw(*field);
    cv::imshow("TetrisCV", image);
}

void GraphicManager::init() const {
    cv::imshow("TetrisCV", image);
}


