#include "vector.h"
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

float vector3::dot( const vector3 & operand ) {
	return x * operand.x + y * operand.y + z * operand.z;
}

vector3::~vector3(){

}

vector3 vector3::operator*( const vector3 & operand ) {
	float xtmp = x * operand.x;
	float ytmp =  y * operand.y;
	float ztmp = z * operand.z;

	return vector3( xtmp, ytmp, ztmp );
}

vector3 vector3::operator*( float scalar ) {
	float xtmp = x * scalar;
	float ytmp =  y * scalar;
	float ztmp = z * scalar;

	return vector3( xtmp, ytmp, ztmp );
}

vector3 vector3::operator+( const vector3 & operand ) {
	float xtmp = x + operand.x;
	float ytmp =  y + operand.y;
	float ztmp = z + operand.z;

	return vector3( xtmp, ytmp, ztmp );
}

vector3 vector3::operator-( const vector3 & operand ) {
	float xtmp = x - operand.x;
	float ytmp =  y - operand.y;
	float ztmp = z - operand.z;

	return vector3( xtmp, ytmp, ztmp );
}

void vector3::operator=( const vector3 & right ) {
	x = right.x;
	y = right.y;
	z = right.z;
}

//VECTOR 4
vector4::vector4() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

vector4::vector4(float x) {
	this->x = x;
	y = 0;
	z = 0;
	w = 0;
}

vector4::vector4(float x, float y) {
	this->x = x;
	this->y = y;
	z = 0;
	w = 0;
}

vector4::vector4(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	w = 0;
}

vector4::vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vector4 vector4::operator * ( const vector4 & vec) {
	return vector4( x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

//TODO figure out how to use mat4 correctly
vector4 vector4::operator*( const mat4 & ) {
	float xNew = ( x + x );
	return vector4();
}

vector4 vector4::operator * (float scalar) {
	return vector4( x * scalar, y * scalar, z * scalar, w * scalar );
}

vector4 vector4::operator+( const vector4 & vec) {
	return vector4( x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

vector4 vector4::operator-( const vector4 & vec) {
	return vector4( x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

float vector4::dot( vector4 & operand ) {
	return x * operand.x + y * operand.y + z * operand.z + w * operand.w;
}

void applyMatrix( mat4& );

void vector4::scaleX( float scalar ) {
	x *= scalar;
}

void vector4::scaleY(float scalar) {
	y *= scalar;
}

void vector4::scaleZ(float scalar) {
	z *= scalar;
}

float vector4::length() {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

vector4 vector4::normalize() {
	float length = this->length();
	return vector4( x/length, y/length, z/length, w/length);
}

float vector4::xVal() {
	return x;
}

float vector4::yVal() {
	return y;
}

float vector4::zVal() {
	return z;
}

float vector4::wVal() {
	return w;
}

vector4 vector4::lerp( vector4 destination, float percentTo) {
	vector4 tmp = vector4(x, y, z, w);
	return (tmp * (1-percentTo)) + destination * percentTo;
}

vector4::~vector4() {
}
