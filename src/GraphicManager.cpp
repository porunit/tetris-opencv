#include "GraphicManager.hpp"
#include "Status.hpp"

#define yellow_rgb {0, 255, 255}
#define green_rgb {0, 255, 0}
#define blue_rgb {255, 144, 30}
#define red_rgb {0, 0, 255}
#define orange_rgb {0, 69, 255}
#define white_rgb {255, 255, 255}

void GraphicManager::drawField(std::vector<std::vector<int>> field) {
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
                    CUBE_THICKNESS
            );
        }
    }
}

cv::Scalar GraphicManager::identifyColor(int code) {
    switch (code) {
        case 1:
            return yellow_rgb;
        case 2:
            return green_rgb;
        case 3:
            return blue_rgb;
        case 4:
            return red_rgb;
        case 5:
            return orange_rgb;
        default:
            return white_rgb;
    }
}

void GraphicManager::clear() {
    image = cv::Mat::zeros(FIELD_ROWS, FIELD_COLS + SCORE_COLS, CV_8UC3);
}

void GraphicManager::update(std::vector<std::vector<int>> *field, int score, Status status) {
    clear();
    drawField(*field);
    drawMenu(score);
    if (status == Status::END) {
        drawDefeatScreen();
    }
    drawControls();
    cv::imshow(WINDOW_NAME, image);
}

void GraphicManager::init() {
    image = cv::Mat::zeros(IMAGE_ROWS, IMAGE_COLS, CV_8UC3);
}

void GraphicManager::drawDefeatScreen() {
    cv::putText(image, "YOU DIED",
                cv::Point(FIELD_COLS + SCORE_COLS / 4, IMAGE_ROWS / 2.5),
                cv::FONT_HERSHEY_SIMPLEX,
                1,
                cv::Scalar(red_rgb),
                2);
    cv::putText(image, "Press ENTER To Restart",
                cv::Point(FIELD_COLS + SCORE_COLS / 12, static_cast<int>(IMAGE_ROWS / 2.25)),
                cv::FONT_HERSHEY_SIMPLEX,
                0.7,
                cv::Scalar(white_rgb),
                1);
}

void GraphicManager::drawControls() {
    cv::putText(image, "a - Left",
                cv::Point(FIELD_COLS + SCORE_COLS / 12, static_cast<int>(IMAGE_ROWS / 1.5)),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(white_rgb),
                1);
    cv::putText(image, "d - Right",
                cv::Point(FIELD_COLS + SCORE_COLS / 12, static_cast<int>(IMAGE_ROWS / 1.5) + MEASURE),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(white_rgb),
                1);
    cv::putText(image, "space - Skip",
                cv::Point(FIELD_COLS + SCORE_COLS / 12, static_cast<int>(IMAGE_ROWS / 1.5) + 2 * MEASURE),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(white_rgb),
                1);
    cv::putText(image, "r - Rotate",
                cv::Point(FIELD_COLS + SCORE_COLS / 12, static_cast<int>(IMAGE_ROWS / 1.5) + 3 * MEASURE),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(white_rgb),
                1);
    cv::putText(image, "esc - Exit",
                cv::Point(FIELD_COLS + SCORE_COLS / 12, static_cast<int>(IMAGE_ROWS / 1.5) + 4 * MEASURE),
                cv::FONT_HERSHEY_SIMPLEX,
                0.9,
                cv::Scalar(white_rgb),
                1);
}

void GraphicManager::drawMenu(int score) {
    int scoreX = calculateScoreX(score);
    cv::line(image, cv::Point(FIELD_COLS, 0),
             cv::Point(FIELD_COLS, FIELD_ROWS),
             cv::Scalar(white_rgb),
             2);
    cv::putText(image, "Scores",
                cv::Point(FIELD_COLS + SCORE_COLS / 3, MEASURE),
                cv::FONT_HERSHEY_SIMPLEX,
                1,
                cv::Scalar(white_rgb),
                2);
    cv::putText(image, std::to_string(score),
                cv::Point(scoreX, 2 * MEASURE),
                cv::FONT_HERSHEY_SIMPLEX,
                1,
                cv::Scalar(white_rgb),
                2);
    cv::putText(image, "Level : " + std::to_string(calcLevel(score) + 1),
                cv::Point(FIELD_COLS + static_cast<int>(SCORE_COLS / 3.3), 4 * MEASURE),
                cv::FONT_HERSHEY_SIMPLEX,
                1,
                cv::Scalar(white_rgb),
                2);
}

int GraphicManager::calculateScoreX(int score) {
    int scoreX = FIELD_COLS + SCORE_COLS / 3 + (MEASURE);
    if (score >= 10 && score < 100) {
        scoreX = FIELD_COLS + SCORE_COLS / 3 + static_cast<int>(0.5 * MEASURE);
    }
    if (score >= 100 && score < 1000) {
        scoreX = FIELD_COLS + SCORE_COLS / 3 + static_cast<int>(0.3 * MEASURE);
    }
    if (score >= 1000 && score < 10000) {
        scoreX = FIELD_COLS + SCORE_COLS / 3;
    }
    return scoreX;
}

int GraphicManager::calcLevel(int score) {
    int level = 0;
    if (score >= 100 && score < 1000) {
        level++;
    }
    if (score >= 1000) {
        level++;
    }
    return level;
}

