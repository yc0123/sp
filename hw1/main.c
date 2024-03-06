#include <stdio.h>
#include "matrix.h"

int main() {
    Matrix A=createMatrix(3,3);
    for(int a=0;a<A.cols*A.rows;a++)
    {
        A.data[a]=a+1;
    }
    Matrix Mat=transpose(A);
    dump(Mat);
    printf("\n");
    Mat=add(A,A);
    dump(Mat);
    printf("\n");
    Mat=multiply(A,A);
    dump(Mat);
    printf("\n");
    Mat=reshape(A,1,9);
    dump(Mat);
}
