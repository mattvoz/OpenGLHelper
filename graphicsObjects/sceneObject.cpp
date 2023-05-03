#include "sceneObject.h"

sceneObject::sceneObject() {
    mesh = new Mesh();
    shader = new Shader();
    rotation = GLMatrix::matrix4();
    scale = GLMatrix::matrix4();
    position = GLVector::vector3();
}

sceneObject::sceneObject( Mesh * mesh, Shader * shader ) {
    this->mesh = mesh;
    this->shader = shader;
}

void sceneObject::render( GLMatrix::matrix4 & world, GLMatrix::matrix4 & view, GLMatrix::matrix4 & perspective ) {
    // Render current object
    unsigned int program = shader->getProgram();
    this->shader->setVariable(mat4 ,"world", &world);
    this->shader->setVariable(mat4 ,"view", &view);
    this->shader->setVariable(mat4, "projection", & perspective);
    glUseProgram( program );
    printf("shader program %d", program);
    mesh->applyBuffers(program);
    shader->applyVariables();
    glDrawArrays(GL_TRIANGLES, 0, mesh->verticeCount() * 3 );
    glUseProgram(NULL);
    if( needsTransformCompute ) {
        this->computeTransformation();
    }
    //Render children
    for(int i = 0; i < children.size(); i++) {
        GLMatrix::matrix4 childWorld = world * this->transformationMatrix;
        children[i]->object->render( childWorld, view, perspective );
    }
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

void sceneObject::rotate( float x, float y, float z) {
}

void sceneObject::computeTransformation() {
}

sceneObject::~sceneObject() {
    delete this->mesh;
    delete this->shader;
}