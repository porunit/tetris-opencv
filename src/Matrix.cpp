#include <iostream>
#include "matrix.hpp"

Matrix::Matrix(int width, int height) : _width(width), _height(height) {
    matrixData = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

int Matrix::getWidth() const {
    return _width;
}

int Matrix::getHeight() const {
    return _height;
}

std::vector<std::vector<int>> &Matrix::getMatrixData() {
    return matrixData;
}

Matrix::Matrix(std::vector<std::vector<int>> source) : _width(source.size()),
                                                        _height(source[0].size()),
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

    for (int i = 0; i < resultHeight; ++i) {
        for (int j = 0; j < resultWidth; ++j) {
            int sum = 0;
            for (int k = 0; k < matrix1.getWidth(); ++k) {
                sum += matrix1.getMatrixData()[i][k] * matrix2.getMatrixData()[k][j];
            }
            res.getMatrixData()[i][j] = sum;
        }
    }

    return res;
}