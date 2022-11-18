#include "vecmat.h"
#include <math.h>

using namespace GLVector;

vector2::vector2() {
	this->x = 0;
	this->y = 0;
}

vector2::vector2(float x) {
	this->x = x;
	this->y = 0;
}

vector2::vector2(float x , float y) {
	this->x = x;
	this->y = y;
}

/**
 * @brief Componenet wise multiplication
 * 
 * @param vec 
 * @return GLVector::vector2 
 */
vector2 vector2::operator*(const vector2 & vec) {
	return vector2( this->x * vec.x, this->y * vec.y);
}

float vector2::dot( vector2 & vec ) {
	return( x * vec.x + y * vec.y);
}

float vector2::xVal() {
	return x;
}

float vector2::yVal(){
	return y;
}

float vector2::length() {
	return std::sqrt( ( x * x + y * y ) );
}

vector2 vector2::normalize() {
	return vector2( x / this->length(), y / this->length() );
}


// Vector 3

vector3::vector3() {
	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
}

vector3::vector3(float x) {
	this->x = x;
	y = 1.0f;
	z = 1.0f;
}

vector3::vector3(float x, float y) {
	this->x = x;
	this->y = y;
	z = 1.0f;
}

vector3::vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}