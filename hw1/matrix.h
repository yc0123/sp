#ifndef MATRIX_H
#define MATRIX_H

typedef struct{
    int rows;
    int cols;
    double* data;
} Matrix;

Matrix createMatrix(int rows, int cols);
Matrix transpose(Matrix mat);
Matrix add(Matrix mat1, Matrix mat2);
Matrix multiply(Matrix mat1, Matrix mat2);
void dump(Matrix mat);
Matrix reshape(Matrix mat, int newRows, int newCols);

#endif