#include "matrix.h"
#include "vec.h"
#include <stdio.h>

using namespace GLMatrix;

matrix2::matrix2() {
    this->values[0] = 1;
    this->values[1] = 0;
    this->values[2] = 0;
    this->values[3] = 1;
}

matrix2::matrix2( float values[4] ) {
    this->values[0] = values[0];
    this->values[1] = values[1];
    this->values[2] = values[2];
    this->values[3] = values[3];
}

matrix2::matrix2( float * values) {
    for(int i = 0; i < 4 ; i++) {
        this->values[i] = values[i];
    }

}

matrix2::matrix2( float zero, float one, float two, float three) {
    values[0] = zero;
    values[1] = one;
    values[2] = two;
    values[3] = three;
}

matrix2::~matrix2() {

}

void matrix2::transpose() {
    float tmp = values[2];
    values[2] = values[1];
    values[1] = tmp;
}
float* matrix2::toArray() {
    float tmp[4];
    for(int i = 0; i < 4; i++) {
        tmp[i] = values[i];
    }

    return tmp;
}

matrix3::matrix3() {
    for(int i = 0; i < 9; i++) {
        if( i == 0 || i == 4 || i==8 ) {
            values[i] = 1;
            continue;
        }
        values[i] = 0;
    }
}

matrix3::matrix3(float values[9]) {
    for(int i = 0; i < 9; i++) {
        this->values[i] = values[i];
    }
}

matrix3::matrix3(float * values) {
    for(int i = 0; i < 9; i++) {
        this->values[i] = values[i];
    }
}

matrix3::~matrix3() {    
}

matrix3 matrix3::operator*(matrix3 & mat) {
    float values[9] = {
        values[0] * mat.get(0,0), 
        values[1] * mat.get(1,0),
        values[2] * mat.get(2,0),
        values[3] * mat.get(0,1),
        values[4] * mat.get(1,1),
        values[5] * mat.get(2,1),
        values[6] * mat.get(0,2),
        values[7] * mat.get(1,2),
        values[8] * mat.get(2,2),
    };

    return matrix3(values);
}

float matrix3::get( int row, int column) {
    return values[row * 3 + column];
}