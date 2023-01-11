#include "matrix.h"
#include "vector.h"
#include <stdio.h>

int main( int argc, char * argv[] ) {
    GLMatrix::matrix4 x = GLMatrix::matrix4();

    GLVector::vector3 posEye = GLVector::vector3(1,0,0);
    GLVector::vector3 lookAt = GLVector::vector3(0,0,0);
    GLVector::vector3 up = GLVector::vector3(0,1,0);

    x = x.lookAt(posEye, lookAt, up);

    x.print();
}