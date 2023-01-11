#include "GLCamera.h"
#include <matrix.h>
#include <math.h>

GLCamera::GLCamera() {
    this->near = 0.01;
    this->far = 1000;
    this->aspect = 16.0f/9.0f;
    this->fov = 70;
    this->position = GLVector::vector3(1,1,1);
    this->rotationMatrix = GLMatrix::matrix4();
    this->viewMatrix = GLMatrix::matrix4();

    this->updatePerspective();
    this->updateView();
}

GLCamera::GLCamera(float fov, float aspect, float near, float far) {
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
    this->position = GLVector::vector3(1,1,1);
    this->rotationMatrix = GLMatrix::matrix4();
    this->viewMatrix = GLMatrix::matrix4();

    this->updatePerspective();
    this->updateView();
}

void GLCamera::updatePerspective() {
    float top = near * tan( toRadians(fov) / 2);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    perspectiveMatrix.makePerspective(left, right, top, bottom, near, far);
}

void GLCamera::updateView() {
    float * tmp = rotationMatrix.toArray();

    tmp[12] = position.xVal();
    tmp[13] = position.yVal();
    tmp[14] = position.zVal();

    viewMatrix = GLMatrix::matrix4(tmp);
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
    this->updateView();
}

void GLCamera::rotateY( float degrees ) {
    viewMatrix.rotateY( degrees );
}

void GLCamera::rotateZ( float degrees ) {
    viewMatrix.rotateZ( degrees );
}

void GLCamera::translate( float x, float y, float z ) {
    position = ( position + GLVector::vector3(x,y,z) );
    this->updateView();
}

void GLCamera::moveTo( GLVector::vector3 newPos ) {
    this->position = newPos;
    this->updateView();
}

void GLCamera::lookAt( GLVector::vector3 & at ) {
    GLVector::vector3 tmp = GLVector::vector3(0,1,0);
    rotationMatrix = rotationMatrix.lookAt( position, at, tmp );
    rotationMatrix.print();
    this->updateView();
}