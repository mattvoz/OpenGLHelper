#include "matrix.h"
#include "vector.h"
#include <stdio.h>

int main( int argc, char * argv[] ) {
    float test[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    GLMatrix::matrix4 * x = new GLMatrix::matrix4(test);
    GLMatrix::matrix4 * y = new GLMatrix::matrix4(test);

    GLMatrix::matrix4 z = (*x) * (*y);

    *x = *x * *y;

    printf("%f \n", x->get(0,2));
    x->transpose();
    x->print();
}