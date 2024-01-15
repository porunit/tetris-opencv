#include <opencv2/opencv.hpp>
#include "matrix.hpp"
#include "Figure.hpp"
#include "Field.hpp"
#include "GameManager.hpp"

int main() {
    auto *manager = new GameManager;
    manager->start();
}
