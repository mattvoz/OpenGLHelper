#include "camera.h"
#include <matrix.h>

camera::camera() {
    this->zNear = 0.01;
    this->zFar = 1000;
    this->aspect = 16/9;
    this->fov = 60;
    this->position = GLVector::vector3(0,0,0);
}

camera::camera(float aspect, float fov, float zNear, float zFar) {
    this->aspect = aspect;
    this->fov = fov;
    this->zNear = zNear;
    this->zFar = zFar;
    this->position = GLVector::vector3(0,0,0);
}