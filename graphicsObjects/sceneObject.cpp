#include "sceneObject.h"

glSceneObject::glSceneObject() {
    this->mesh = new glMesh();
    this->shader = new shader();
}

glSceneObject( glMesh * mesh, shader * shader ) {
    this->mesh = mesh;
    this->shader = shader;
}

void glSceneObject::render( GLMatrix::matrix4 & world ) {
    shader.applyVariables();
}

void glSceneObject::setMesh( glMesh * newMesh ) {
    glMesh * oldMesh = this->mesh;
    this->mesh = newMesh;
    delete oldMesh;
}
void glSceneObject::setShader( shader * newShader ) {
    shader * tmpShader = this->shader;
    this->shader = newShader;
    delete tmpShader;
}
glSceneObject::~glSceneObject() {
    delete this->mesh;
    delete this->shader;
}