#pragma once

#include <vector>

class Matrix {
    int _width;
    int _height;
    std::vector<std::vector<int>> matrixData;
public:
    Matrix(int width, int height);
    Matrix(std::vector<std::vector<int>> source);

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    std::vector<std::vector<int>> &getMatrixData();
};

std::ostream& operator<<(std::ostream& os, Matrix& mat);

Matrix operator+(Matrix &mat1, Matrix &mat2);

Matrix operator*(Matrix &matrix1, Matrix &matrix2);
