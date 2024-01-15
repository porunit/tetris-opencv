#include <iostream>
#include "matrix.hpp"

Matrix::Matrix(int width, int height) : width(width), height(height) {
    matrixData = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

int Matrix::getWidth() const {
    return width;
}

int Matrix::getHeight() const {
    return height;
}

std::vector<std::vector<int>> &Matrix::getMatrixData() {
    return matrixData;
}

Matrix::Matrix(std::vector<std::vector<int>> source) : width(source.size()),
                                                       height(source[0].size()),
                                                       matrixData(source) {}


std::ostream &operator<<(std::ostream &os, Matrix &mat) {
    for (size_t it = 0; it < mat.getHeight(); ++it) {
        for (size_t jt = 0; jt < mat.getWidth(); ++jt) {
            os << mat.getMatrixData()[it][jt] << " ";
        }
        os << std::endl;
    }
    return os;
}


Matrix operator+(Matrix &mat1, Matrix &mat2) {
    if (mat1.getHeight() != mat2.getHeight() || mat1.getWidth() != mat2.getWidth()) {
        throw std::invalid_argument("Matrix dimension mismatch");
    }
    Matrix res(mat1.getWidth(), mat1.getHeight());

    for (size_t it = 0; it < mat1.getWidth(); ++it) {
        for (size_t jt = 0; jt < mat1.getHeight(); ++jt) {
            res.getMatrixData().at(it).at(jt) =
                    mat1.getMatrixData().at(it).at(jt) + mat2.getMatrixData().at(it).at(jt);
        }
    }

    return res;
}

Matrix operator*(Matrix &matrix1, Matrix &matrix2) {
    int resultWidth = matrix2.getWidth();
    int resultHeight = matrix1.getHeight();

    if (matrix1.getWidth() != matrix2.getHeight()) {
        throw std::invalid_argument("Matrix dimension mismatch");
    }

    Matrix res(resultWidth, resultHeight);

    for (int y = 0; y < resultHeight; ++y) {
        for (int x = 0; x < resultWidth; ++x) {
            int sum = 0;
            for (int k = 0; k < matrix1.getWidth(); ++k) {
                sum += matrix1.getMatrixData()[y][k] * matrix2.getMatrixData()[k][x];
            }
            res.getMatrixData()[y][x] = sum;
        }
    }

    return res;
}