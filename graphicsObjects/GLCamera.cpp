#include "GLCamera.h"
#include <matrix.h>
#include <math.h>

GLCamera::GLCamera() {
    this->near = 0.01;
    this->far = 1000;
    this->aspect = 16.0f/9.0f;
    this->fov = 70;
    this->position = GLVector::vector3(0,0,0);

    this->updatePerspective();

    this->viewMatrix = GLMatrix::matrix4();
}

GLCamera::GLCamera(float fov, float aspect, float near, float far) {
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
    this->position = GLVector::vector3(0,0,0);

    this->updatePerspective();

    this->viewMatrix = GLMatrix::matrix4();
}

void GLCamera::updatePerspective() {
    float top = near * tan( toRadians(fov) / 2);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    perspectiveMatrix.makePerspective(left, right, top, bottom, near, far);
}

void GLCamera::updateAspect(float newAspect) {
    aspect = newAspect;
}

void GLCamera::updateFov( float newFov ) {
    fov = newFov;
}

void GLCamera::updateNear(float newNear) {
    near = newNear;
}

void GLCamera::updateFar(float newFar) {
    far = newFar;
}

GLMatrix::matrix4 & GLCamera::getPerspective() {
    return perspectiveMatrix;
}

GLMatrix::matrix4& GLCamera::getViewMatrix() {
    return viewMatrix;
}

void GLCamera::rotateX( float degrees ) {
    viewMatrix.rotateX( degrees );
}

void GLCamera::rotateY( float degrees ) {
    viewMatrix.rotateY( degrees );
}

void GLCamera::rotateZ( float degrees ) {
    viewMatrix.rotateZ( degrees );
}

void GLCamera::translate( float x, float y, float z ) {
}
