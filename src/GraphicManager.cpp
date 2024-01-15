#include "GraphicManager.hpp"
#include "Status.hpp"

//TODO CHECK RESTART PAUSE END CYCLE
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
    image = cv::Mat::zeros(FIELD_ROWS, FIELD_COLS + SCORE_COLS, CV_8UC3);  // Adjusted the width
}

//TODO ref to funs
void GraphicManager::update(std::vector<std::vector<int>> *field, int score, Status status) {
    clear();
    draw(*field);
    cv::line(image, cv::Point(FIELD_COLS, 0),
             cv::Point(FIELD_COLS, FIELD_ROWS),
             cv::Scalar(255, 255, 255),
             2);
    cv::putText(image, "Scores",
                cv::Point(FIELD_COLS + 110, 50),
                cv::FONT_HERSHEY_SIMPLEX,
                1,
                cv::Scalar(255, 255, 255),
                2);
    cv::putText(image, std::to_string(score),
                cv::Point(FIELD_COLS + 120, 100),
                cv::FONT_HERSHEY_SIMPLEX,
                1,
                cv::Scalar(255, 255, 255),
                2);
    if (status == Status::END) {
        cv::putText(image, "YOU DIED",
                    cv::Point(FIELD_COLS + 70, 400),
                    cv::FONT_HERSHEY_SIMPLEX,
                    1,
                    cv::Scalar(0, 0, 255),
                    2);
        cv::putText(image, "Press ENTER To Restart",
                    cv::Point(FIELD_COLS + 20, 500),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.7,
                    cv::Scalar(255, 255, 255),
                    1);
    }
    cv::putText(image, "a - Left",
                cv::Point(FIELD_COLS + 20, 700),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(255, 255, 255),
                1);
    cv::putText(image, "b - Right",
                cv::Point(FIELD_COLS + 20, 750),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(255, 255, 255),
                1);
    cv::putText(image, "space - Skip",
                cv::Point(FIELD_COLS + 20, 800),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(255, 255, 255),
                1);
    cv::putText(image, "r - Rotate",
                cv::Point(FIELD_COLS + 20, 850),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(255, 255, 255),
                1);
    cv::putText(image, "esc - exit",
                cv::Point(FIELD_COLS + 20, 900),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(255, 255, 255),
                1);
    // Display the updated image
    cv::imshow("TetrisCV", image);
}

void GraphicManager::init() {
    image = cv::Mat::zeros(IMAGE_ROWS, IMAGE_COLS, CV_8UC3);
    cv::imshow("TetrisCV", image);
}


