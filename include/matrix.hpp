#pragma once

#include <vector>

class Matrix {
    int width;

    int height;
    std::vector<std::vector<int>> matrixData;
public:
    Matrix(std::vector<std::vector<int>> source);

    Matrix(int width, int height);

    int getWidth() const;

    int getHeight() const;

    std::vector<std::vector<int>> &getMatrixData();
};

std::ostream &operator<<(std::ostream &os, Matrix &mat);

Matrix operator+(Matrix &mat1, Matrix &mat2);

Matrix operator*(Matrix &matrix1, Matrix &matrix2);
