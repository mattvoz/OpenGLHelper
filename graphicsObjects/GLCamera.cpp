#include "glCamera.h"
#include <math.h>
#include <stdio.h>

glCamera::glCamera() {
	this->near = 0.1;
	this->far = 1000;
	this->aspect = 16.0f/9.0f;
	this->fov = 70;
	this->position = GLVector::vector3(1,1,1);
	this->rotationMatrix = GLMatrix::matrix4();

	this->perspectiveMatrix = GLMatrix::matrix4();
	this->viewMatrix = GLMatrix::matrix4();

	this->updatePerspective();
	this->updateView();
}

glCamera::glCamera(float fov, float aspect) {
	this->fov = fov;
	this->aspect = aspect;
	this->near = .1;
	this->far = 1000;
	this->position = GLVector::vector3(1,1,1);
	this->rotationMatrix = GLMatrix::matrix4();

	this->perspectiveMatrix = GLMatrix::matrix4();
	this->viewMatrix = GLMatrix::matrix4();

	this->updatePerspective();
	this->updateView();
}

void glCamera::updatePerspective() {
	perspectiveMatrix.makePerspective( fov, aspect, near, far);
}

void glCamera::updateView() {
	GLMatrix::matrix4 tmp = GLMatrix::matrix4();
	tmp.makeTranslation(-position.xVal(), -position.yVal(), -position.zVal());
	GLMatrix::matrix4 tmpRot = rotationMatrix;
	tmpRot.transpose();
	viewMatrix = tmpRot * tmp;
}

void glCamera::updateAspect(float newAspect) {
	aspect = newAspect;
}

void glCamera::updateFov( float newFov ) {
	fov = newFov;
}

void glCamera::updateNear(float newNear) {
	near = newNear;
}

void glCamera::updateFar(float newFar) {
	far = newFar;
}

GLMatrix::matrix4 & glCamera::getPerspective() {
	return perspectiveMatrix;
}

GLMatrix::matrix4& glCamera::getViewMatrix() {
	if(needsUpdate) {
		updateView();
		needsUpdate = false;
	}
	return viewMatrix;
}

void glCamera::rotateX( float degrees ) {
	rotationMatrix.rotateX( degrees );
	needsUpdate = true;
}

void glCamera::rotateY( float degrees ) {
	rotationMatrix.rotateY( degrees );
	needsUpdate = true;
}

void glCamera::rotateZ( float degrees ) {
	rotationMatrix.rotateZ( degrees );
	needsUpdate = true;
}

void glCamera::translate( float x, float y, float z ) {
	position = ( position + GLVector::vector3(x,y,z) );
	needsUpdate = true;
}

void glCamera::moveTo( GLVector::vector3 newPos ) {
	this->position = newPos;
	needsUpdate = true;
}

void glCamera::lookAt( GLVector::vector3 & at ) {
	GLVector::vector3 up = GLVector::vector3(0,1,0);
	rotationMatrix = rotationMatrix.lookAt( position, at, up );
	needsUpdate = true;
}

void glCamera::render( GLMatrix::matrix4 & world, GLMatrix::matrix4 & view, GLMatrix::matrix4 & perspective ) {
	GLMatrix::matrix4 translate = GLMatrix::matrix4();
	translate.set( 0, 3, position.xVal() );
	translate.set( 1, 3, position.yVal() );
	translate.set( 2, 3, position.zVal() );

	GLMatrix::matrix4 childWorld = world * translate * rotationMatrix * scale;

	for( int i = 0; i < children.size(); i++) {
		children[i]->object->render(childWorld, view, perspective);
	}
}

GLMatrix::matrix4& glCamera::getWolrdMatrix() {
	if( ! worldNeedsUpdate ) {
		return localWorldMatrix;
	}
	GLMatrix::matrix4 localWorld = GLMatrix::matrix4();
	localWorld.set( 0, 3, -position.xVal() );
	localWorld.set( 1, 3, -position.yVal() );
	localWorld.set( 2, 3, -position.zVal() );

	localWorldMatrix = localWorld;

	GLMatrix::matrix4 childWorld = localWorld * rotationMatrix * scale;

	worldNeedsUpdate = false;

	return childWorld;
}
	