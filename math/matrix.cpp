#include "vector.h"
#include "matrix.h"
#include <math.h>
#include <stdio.h>

using namespace GLMatrix;

float toRadians( float degrees ) {
    return ( (degrees * M_PI) / 180 );
}

matrix2::matrix2() {
    this->values[0] = 1;
    this->values[2] = 0;
    this->values[1] = 0;
    this->values[3] = 1;
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
    static float tmp[4];
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

matrix3::matrix3(float * values) {
    for(int i = 0; i < 9; i++) {
        this->values[i] = values[i];
    }
}

matrix3::~matrix3() {    
}

matrix3 matrix3::operator*(matrix3 & mat) {
    float values[9] = {
        values[0] * mat.get(0,0) + values[3] * mat.get(1,0) + values[6] * mat.get(2,0),
        values[3] * mat.get(0,1) + values[3] * mat.get(1,1) + values[6] * mat.get(1,1),
        values[6] * mat.get(0,2) + values[3] * mat.get(1,2) + values[6] * mat.get(2,2),
        values[1] * mat.get(0,0) + values[4] * mat.get(1,0) + values[7] * mat.get(2,0),
        values[4] * mat.get(0,1) + values[4] * mat.get(1,1) + values[7] * mat.get(2,1),
        values[7] * mat.get(0,2) + values[4] * mat.get(1,2) + values[7] * mat.get(2,2),
        values[2] * mat.get(0,0) + values[5] * mat.get(1,0) + values[8] * mat.get(2,0),
        values[5] * mat.get(0,1) + values[5] * mat.get(1,1) + values[8] * mat.get(2,1),
        values[8] * mat.get(0,2) + values[5] * mat.get(1,2) + values[8] * mat.get(2,2),
    };

    return matrix3(values);
}

GLVector::vector3 matrix3::operator*(GLVector::vector3 & operand) {
    float x = this->values[0] * operand.xVal() + this->values[3] * operand.yVal() + this->values[6] * operand.zVal();
    float y = this->values[1] * operand.xVal() + this->values[4] * operand.yVal() + this->values[7] * operand.zVal();
    float z = this->values[2] * operand.xVal() + this->values[5] * operand.yVal() + this->values[8] * operand.zVal();

    return GLVector::vector3(x,y,z);
}

void matrix3::transpose() {
    float tmp[9];

    for(int i = 0; i < 9; i++) {
        tmp[i] = this->values[i];
    }

    this->values[0] = tmp[0];
    this->values[1] = tmp[3];
    this->values[2] = tmp[6];
    this->values[3] = tmp[1];
    this->values[4] = tmp[4];
    this->values[5] = tmp[7];
    this->values[6] = tmp[2];
    this->values[7] = tmp[5];
    this->values[8] = tmp[8];
}

float matrix3::get( int row, int column) {
    return values[ row + column * 3];
}

void matrix3::translation(float x, float y) {
    this->makeIdentity();
    values[6] = x;
    values[7] = y;
}

void matrix3::rotation( int degree ) {
    this->makeIdentity();
    float radians = toRadians(degree);

    float c = cos( radians );
    float s = sin( radians );

    this->makeIdentity();
    values[0] = c;
    values[1] = -s;
    values[2] = 0;
    values[3] = s;
    values[4] = c;
    values[5] = 0;
    values[6] = 0;
    values[7] = 0;
    values[8] = 1;
}

void matrix3::scale(float x, float y) {
    this->makeIdentity();

    values[0] = x;
    values[4] = y;
}

void matrix3::makeIdentity() {
    for(int i = 0; i < 9 ; i++) {
        if( i == 0 || i == 4 || i == 8) {
            values[i] = 1;
            continue;
        }
        values[i] = 0;
    }
}

float * matrix3::toArray() {
    static float tmp[9];
    for( int i = 0; i < 9; i++) {
        tmp[i] = this->values[i];
    }

    return tmp;
}

matrix4::matrix4() {
    for(int i = 0 ; i < 16 ; i++) {
        if(i == 0 || i == 5 || i == 10 || i == 15 ) {
            values[i] = 1;
            continue;
        }
        values[i] = 0;
    }
}

matrix4::matrix4( float * array ) {
    for(int i = 0; i < 16; i ++ ) {
        values[i] = array[i];
    }
}

matrix4::~matrix4() {

}

matrix4 matrix4::operator* ( matrix4& operand) {
    float tmp[16];
    tmp[0] = ( values[0] * operand.get(0,0) ) + ( values[4] * operand.get(1,0) ) + ( values[8] * operand.get(2,0) ) + ( values[12] * operand.get(3,0) );
    tmp[4] = ( values[0] * operand.get(0,1) ) + ( values[4] * operand.get(1,1) ) + ( values[8] * operand.get(2,1) ) + ( values[12] * operand.get(3,1) );
    tmp[8] = ( values[0] * operand.get(0,2) ) + ( values[4] * operand.get(1,2) ) + ( values[8] * operand.get(2,2) ) + ( values[12] * operand.get(3,2) );
    tmp[12] = ( values[0] * operand.get(0,3) ) + ( values[4] * operand.get(1,3) ) + ( values[8] * operand.get(2,3) ) + ( values[12] * operand.get(3,3) );

    tmp[1] = ( values[1] * operand.get(0,0) ) + ( values[5] * operand.get(1,0) ) + ( values[9] * operand.get(2,0) ) + ( values[13] * operand.get(3,0) );
    tmp[5] = ( values[1] * operand.get(0,1) ) + ( values[5] * operand.get(1,1) ) + ( values[9] * operand.get(2,1) ) + ( values[13] * operand.get(3,1) );
    tmp[9] = ( values[1] * operand.get(0,2) ) + ( values[5] * operand.get(1,2) ) + ( values[9] * operand.get(2,2) ) + ( values[13] * operand.get(3,2) );
    tmp[13] = ( values[1] * operand.get(0,3) ) + ( values[5] * operand.get(1,3) ) + ( values[9] * operand.get(2,3) ) + ( values[13] * operand.get(3,3) );

    tmp[2] = (values[2] * operand.get(0,0) ) + ( values[6] * operand.get(1,0) ) + ( values[10] * operand.get(2,0) ) + ( values[14] * operand.get(3,0) );
    tmp[6] = ( values[2] * operand.get(0,1) ) + ( values[6] * operand.get(1,1) ) + ( values[10] * operand.get(2,1) ) + ( values[14] * operand.get(3,1) );
    tmp[10] = ( values[2] * operand.get(0,2) ) + ( values[6] * operand.get(1,2) ) + ( values[10] * operand.get(2,2) ) + ( values[14] * operand.get(3,2) );
    tmp[14] = ( values[2] * operand.get(0,3) ) + ( values[6] * operand.get(1,3) ) + ( values[10] * operand.get(2,3) ) + ( values[14] * operand.get(3,3) );

    tmp[3] = (values[3] * operand.get(0,0) ) + ( values[7] * operand.get(1,0) ) + ( values[11] * operand.get(2,0) ) + ( values[15] * operand.get(3,0) );
    tmp[7] = ( values[3] * operand.get(0,1) ) + ( values[7] * operand.get(1,1) ) + ( values[11] * operand.get(2,1) ) + ( values[15] * operand.get(3,1) );
    tmp[11] = ( values[3] * operand.get(0,2) ) + ( values[7] * operand.get(1,2) ) + ( values[11] * operand.get(2,2) ) + ( values[15] * operand.get(3,2) );
    tmp[15] = ( values[3] * operand.get(0,3) ) + ( values[7] * operand.get(1,3) ) + ( values[11] * operand.get(2,3) ) + ( values[15] * operand.get(3,3) );

    return matrix4(tmp);

}

matrix4 matrix4::operator - ( matrix4& operand) {
    float tmp[16];
    tmp[0] = ( values[0] - operand.get(0,0) );
    tmp[4] = ( values[4] - operand.get(1,0) );
    tmp[8] = ( values[8] - operand.get(2,0) );
    tmp[12] = ( values[12] - operand.get(3,0) );

    tmp[1] = ( values[1] - operand.get(0,1) );
    tmp[5] = ( values[5] - operand.get(1,1) );
    tmp[9] = ( values[9] - operand.get(2,1) );
    tmp[13] = ( values[13] - operand.get(3,1) );

    tmp[2] = ( values[2] - operand.get(0,2) );
    tmp[6] = ( values[6] - operand.get(1,2) );
    tmp[10] = ( values[10] - operand.get(2,2) );
    tmp[14] = ( values[14] - operand.get(3,2) );

    tmp[3] = ( values[3] - operand.get(0,3) );
    tmp[7] = ( values[7] - operand.get(1,3) );
    tmp[11] = ( values[11] - operand.get(2,3) );
    tmp[15] = ( values[15] - operand.get(3,3) );

    return matrix4(tmp);

}

matrix4 matrix4::operator + ( matrix4& operand) {
    float tmp[16];
    tmp[0] = ( values[0] + operand.get(0,0) );
    tmp[4] = ( values[4] + operand.get(1,0) );
    tmp[8] = ( values[8] + operand.get(2,0) );
    tmp[12] = ( values[12] + operand.get(3,0) );

    tmp[1] = ( values[1] + operand.get(0,1) );
    tmp[5] = ( values[5] + operand.get(1,1) );
    tmp[9] = ( values[9] + operand.get(2,1) );
    tmp[13] = ( values[13] + operand.get(3,1) );

    tmp[2] = ( values[2] + operand.get(0,2) );
    tmp[6] = ( values[6] + operand.get(1,2) );
    tmp[10] = ( values[10] + operand.get(2,2) );
    tmp[14] = ( values[14] + operand.get(3,2) );

    tmp[3] = ( values[3] + operand.get(0,3) );
    tmp[7] = ( values[7] + operand.get(1,3) );
    tmp[11] = ( values[11] + operand.get(2,3) );
    tmp[15] = ( values[15] + operand.get(3,3) );

    return matrix4(tmp);

}

GLVector::vector4 matrix4::operator* (GLVector::vector4 & operand) {
    float x = operand.xVal() * this->values[0] + operand.yVal() * this->values[4] + operand.zVal() * this->values[8] + operand.wVal() * this->values[12];
    float y = operand.xVal() * this->values[1] + operand.yVal() * this->values[5] + operand.zVal() * this->values[9] + operand.wVal() * this->values[13];
    float z = operand.xVal() * this->values[2] + operand.yVal() * this->values[6] + operand.zVal() * this->values[10] + operand.wVal() * this->values[14];
    float w = operand.xVal() * this->values[3] + operand.yVal() * this->values[7] + operand.zVal() * this->values[11] + operand.wVal() * this->values[15];

    return GLVector::vector4(x,y,z,w);

}

void matrix4::transpose() {
    float tmp[16];
    for(int i = 0; i < 16; i++) {
        tmp[i] = this->values[i];
    }

    this->values[0] = tmp[0];
    this->values[1] = tmp[4];
    this->values[2] = tmp[8];
    this->values[3] = tmp[12];
    this->values[4] = tmp[1];
    this->values[5] = tmp[5];
    this->values[6] = tmp[9];
    this->values[7] = tmp[13];
    this->values[8] = tmp[2];
    this->values[9] = tmp[6];
    this->values[10] = tmp[10];
    this->values[11] = tmp[14];
    this->values[12] = tmp[3];
    this->values[13] = tmp[7];
    this->values[14] = tmp[11];
    this->values[15] = tmp[15];
}

//Zero indexed get
float matrix4::get( int row, int column) {
    return values[row + column * 4];
}

void matrix4::set(int row, int column, float value) {
    values[row + column * 4 ] = value;
}

/**
 * Returns an array copy of whats' in the object on heap don't forget to free once finished.
*/
float * matrix4::toArray() {
    static float tmp[16];
    for(int i = 0; i < 16; i ++) {
        tmp[i] = this->values[i];
    }

    return tmp;
}

void matrix4::makeIdentity(){
    for(int i = 0 ; i < 16 ; i++) {
        if(i == 0 || i == 5 || i == 10 || i == 15 ) {
            values[i] = 1;
            continue;
        }
        values[i] = 0;
    }
}

/**
 * Translation adds to an existing translation for a system so if you want to adjust a object to move +xyz then use this function.
*/
void matrix4::translation( float x, float y, float z ) {
    this->values[12] += x;
    this->values[13] += y;
    this->values[14] += z;
}

/**
 * Retruns a new translation to make so set to a new position.
*/
void matrix4::makeTranslation(float x, float y, float z){
    this->makeIdentity();

    this->values[12] = x;
    this->values[13] = y;
    this->values[14] = z;
}

void matrix4::rotateX( float degrees ){
    float radians = toRadians(degrees);
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);

    this->makeIdentity();

    this->values[5] = cosTheta;
    this->values[6] = sinTheta;

    this->values[9] = -1 * sinTheta;
    this->values[10] = cosTheta;
}

void matrix4::rotateY( float degrees ) {
    float radians = toRadians(degrees);
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);

    this->makeIdentity();

    this->values[0] = cosTheta;
    this->values[2] = -sinTheta;


    this->values[8] = sinTheta;
    this->values[10] = cosTheta;
}

void matrix4::rotateZ( float degrees ) {
    float radians = toRadians(degrees);
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);
    
    this->makeIdentity();

    this->values[0] = cosTheta;
    this->values[1] = sinTheta;
    this->values[4] = -1 * sinTheta;
    this->values[5] = cosTheta;
}

void matrix4::scale( float x, float y, float z ) {
    this->makeIdentity();

    this->values[0] = x;
    this->values[5] = y;
    this->values[10] = z;
}

void matrix4::print() {
    for(int i = 0; i < 16; i++){
        printf( "%f ", this->values[i]);
    }
    printf("\n");
    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j++) {
            printf(" %f", this->get(i,j));
        }
        printf("\n");
    }
}

void matrix4::makePerspective(float left, float right, float top, float bottom, float near, float far) {
    this->makeIdentity();
    float x = 2 * near / (right - left);
    float y = 2 * near / (top - bottom);
    float a = (right + left) / (right - left);
    float b = (top + bottom) / (top - bottom);
    float c = -(far + near) / (far - near);
    float d = -2 * far * near / (far - near);
    
    values[0] = x;
    values[5] = y;
	values[8] = a;
	values[9] = b;
	values[10] = c;
    values[11] = -1;
	values[14] = d;
    values[15] = 0;
}

matrix4 matrix4::lookAt( GLVector::vector3 & eye, GLVector::vector3 & target, GLVector::vector3 & up) {
    GLVector::vector3 z = (eye - target);

    if(z.length() == 0) {
        z.setZ(1);
    }

    z = z.normalize();

    GLVector::vector3 x = (up.crossProduct(z)).normalize();
    GLVector::vector3 y = z.crossProduct(x);

    x.normalize();
    y.normalize();

    float xd = -1 * ( x.dot( eye ) );
    float yd = -1 * ( y.dot( eye ) );
    float zd = -1 * ( z.dot( eye ) );

    float tmp[16] = { x.xVal(), x.yVal(), x.zVal(), 0, y.xVal(), y.yVal(), y.zVal(), 0, z.xVal(), z.yVal(), z.zVal(), 0, 0, 0, 0, 1 };
    return matrix4( tmp );
}
