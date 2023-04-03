#include "sceneObject.h"

sceneObject::sceneObject() {
    mesh = new Mesh();
    shader = new Shader();
}

sceneObject::sceneObject( Mesh * mesh, Shader * shader ) {
    this->mesh = mesh;
    this->shader = shader;
}

void sceneObject::render( GLMatrix::matrix4 & world ) {
    shader->applyVariables();
    unsigned int program = shader->getProgram();
    mesh->applyBuffers(program);
}

void sceneObject::setMesh( Mesh * newMesh ) {
    Mesh * oldMesh = this->mesh;
    this->mesh = newMesh;
    delete oldMesh;
}

void sceneObject::setShader( Shader * newShader ) {
    Shader * tmpShader = this->shader;
    this->shader = newShader;
    delete tmpShader;
}

sceneObject::~sceneObject() {
    delete this->mesh;
    delete this->shader;
}