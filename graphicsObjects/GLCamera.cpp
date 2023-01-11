#include "GLCamera.h"
#include <matrix.h>
#include <math.h>
#include <stdio.h>

GLCamera::GLCamera() {
    this->near = 0.1;
    this->far = 1000;
    this->aspect = 16.0f/9.0f;
    this->fov = 70;
    this->position = GLVector::vector3(1,1,1);
    this->rotationMatrix = GLMatrix::matrix4();
    this->viewMatrix = GLMatrix::matrix4();

    this->updatePerspective();
    this->updateView();
}

GLCamera::GLCamera(float fov, float aspect) {
    this->fov = fov;
    this->aspect = aspect;
    this->near = .1;
    this->far = 1000;
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
    GLMatrix::matrix4 tmp = GLMatrix::matrix4();
    tmp.set( 0, 3, -position.xVal() );
    tmp.set( 1, 3, -position.yVal() );
    tmp.set( 2, 3, -position.zVal() );
    GLMatrix::matrix4 tmpRot = rotationMatrix;
    tmpRot.transpose();
    viewMatrix = tmpRot * tmp;
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
    if(needsUpdate) {
        updateView();
        needsUpdate = false;
    }
    return viewMatrix;
}

void GLCamera::rotateX( float degrees ) {
    viewMatrix.rotateX( degrees );
    needsUpdate = true;
}

void GLCamera::rotateY( float degrees ) {
    viewMatrix.rotateY( degrees );
    needsUpdate = true;
}

void GLCamera::rotateZ( float degrees ) {
    viewMatrix.rotateZ( degrees );
    needsUpdate = true;
}

void GLCamera::translate( float x, float y, float z ) {
    position = ( position + GLVector::vector3(x,y,z) );
    needsUpdate = true;
}

void GLCamera::moveTo( GLVector::vector3 newPos ) {
    this->position = newPos;
    needsUpdate = true;
}

void GLCamera::lookAt( GLVector::vector3 & at ) {
    GLVector::vector3 up = GLVector::vector3(0,1,0);
    rotationMatrix = rotationMatrix.lookAt( position, at, up );
    needsUpdate = true;
}