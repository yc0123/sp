#include <stdio.h>
#include "matrix.h"

int main() {
    Matrix A=createMatrix(3,3);
    Matrix B=createMatrix(3,3);
    for(int a=0;a<A.cols*A.rows;a++)
    {
        A.data[a]=a+1;
        B.data[a]=a+1;
    }
    Matrix C=transpose(A);
    dump(C);
    printf("\n");
    Matrix D=add(A,B);
    dump(D);
    printf("\n");
    Matrix E=multiply(A,B);
    dump(E);
    printf("\n");
    Matrix F=createMatrix(2,3);
    for(int a=0;a<F.rows*F.cols;a++)
    {
        F.data[a]=a+1;
    }
    Matrix G=reshape(F,3,2);
    dump(G);
    printf("\n");
}
