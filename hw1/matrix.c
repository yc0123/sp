#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix createMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double*)malloc(rows * cols * sizeof(double));
    return mat;
}

Matrix transpose(Matrix mat) {
    Matrix result = createMatrix(mat.cols, mat.rows);

    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            result.data[j * result.rows + i] = mat.data[i * mat.cols + j];
        }
    }

    return result;
}

Matrix add(Matrix mat1, Matrix mat2) {
    if (mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
        printf("Error: Matrix dimensions do not match for addition.\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = createMatrix(mat1.rows, mat1.cols);

    for (int i = 0; i < mat1.rows * mat1.cols; ++i) {
        result.data[i] = mat1.data[i] + mat2.data[i];
    }

    return result;
}

Matrix multiply(Matrix mat1, Matrix mat2) {
    if (mat1.cols != mat2.rows) {
        printf("Error: Matrix dimensions do not match for multiplication.\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = createMatrix(mat1.rows, mat2.cols);

    for (int i = 0; i < mat1.rows; ++i) {
        for (int j = 0; j < mat2.cols; ++j) {
            result.data[i * result.cols + j] = 0.0;
            for (int k = 0; k < mat1.cols; ++k) {
                result.data[i * result.cols + j] += mat1.data[i * mat1.cols + k] * mat2.data[k * mat2.cols + j];
            }
        }
    }

    return result;
}

void dump(Matrix mat) {
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            printf("%f ", mat.data[i * mat.cols + j]);
        }
        printf("\n");
    }
}

Matrix reshape(Matrix mat, int newRows, int newCols) {
    if (mat.rows * mat.cols != newRows * newCols) {
        fprintf(stderr, "Error: Number of elements must remain the same for reshaping.\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = createMatrix(newRows, newCols);

    for (int i = 0; i < newRows * newCols; ++i) {
        result.data[i] = mat.data[i];
    }

    return result;
}
