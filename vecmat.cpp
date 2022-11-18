#include "vecmat.h"

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