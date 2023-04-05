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
    unsigned int program = shader->getProgram();
    glUseProgram( program );
    printf("shader program %d", program);
    mesh->applyBuffers(program);
    shader->applyVariables();
    glDrawArrays(GL_TRIANGLES, 0, mesh->verticeCount() * 3 );

    glUseProgram(NULL);
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