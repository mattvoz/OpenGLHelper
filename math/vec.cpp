#include "vec.h"
#include <cmath>
#include <stdio.h>

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
	float length = this->length();
	return GLVector::vector2( x / length, y / length );
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

vector3 vector3::operator*( const vector3 & vec ) {
	return vector3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

vector3 vector3::crossProduct( const vector3 & vec ){
	return vector3( this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
}

float vector3::xVal() {
	return x;
}

float vector3::yVal() {
	return y;
}

float vector3::zVal() {
	return z;
}

float vector3::length() {
	return std::sqrt( x * x + y * y + z * z);
}

vector3 vector3::normalize() {
	float length = this->length();
	return vector3( x / length, y / length, z / length );
}

vector3::~vector3(){

}