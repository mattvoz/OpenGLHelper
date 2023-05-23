#include "sceneObject.h"

sceneObject::sceneObject() {
    mesh = new Mesh();
    shader = new Shader();
    rotation = GLMatrix::matrix4();
    scaleMatrix = GLMatrix::matrix4();
    position = GLVector::vector3();
}

sceneObject::sceneObject( Mesh * mesh, Shader * shader ) {
    this->mesh = mesh;
    this->shader = shader;
    rotation = GLMatrix::matrix4();
    scaleMatrix = GLMatrix::matrix4();
    position = GLVector::vector3();
}

void sceneObject::render( GLMatrix::matrix4 & world, GLMatrix::matrix4 & view, GLMatrix::matrix4 & perspective ) {
    if( needsTransformCompute ) {
        this->computeTransformation();
        needsTransformCompute = false;
    }
    // Render current object
    unsigned int program = shader->getProgram();
    this->shader->setVariable(mat4 ,"world", &world);
    this->shader->setVariable(mat4 ,"view", &view);
    this->shader->setVariable(mat4, "projection", & perspective);
    this->shader->setVariable(mat4, "model", &this->transformationMatrix);
    glUseProgram( program );
    mesh->applyBuffers(program);
    shader->applyVariables();
    glDrawArrays(GL_TRIANGLES, 0, mesh->verticeCount() * 3 );
    glUseProgram(NULL);
    //Render children
    for(int i = 0; i < children.size(); i++) {
        GLMatrix::matrix4 childWorld = world * this->transformationMatrix;
        children[i]->object->render( childWorld, view, perspective );
    }
}

Mesh * sceneObject::getMesh() {
    return this->mesh;
}

Shader * sceneObject::getShader() {
    return this->shader;
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
    GLMatrix::matrix4 xMat = GLMatrix::matrix4();
    xMat.rotateX(x);
    GLMatrix::matrix4 yMat = GLMatrix::matrix4();
    yMat.rotateY(y);
    GLMatrix::matrix4 zMat = GLMatrix::matrix4();
    zMat.rotateZ(z);
    this->rotationMatrix = xMat * yMat * zMat;
    this->needsTransformCompute = true;
}

void sceneObject::translate( float x, float y, float z ) {
    this->position = this->position + GLVector::vector3(x,y,z);
    this->needsTransformCompute = true;
}

void sceneObject::scale( float x, float y, float z ) {
    scaleMatrix.scale(x,y,z);
    this->needsTransformCompute = true;
}

void sceneObject::computeTransformation() {
    GLMatrix::matrix4 tranlsationMat =  GLMatrix::matrix4();
    tranlsationMat.set( 0,3,this->position.xVal() );
    tranlsationMat.set( 1,3,this->position.yVal() );
    tranlsationMat.set( 2,3,this->position.zVal() );
    this->transformationMatrix = tranlsationMat * this->rotationMatrix * this->scaleMatrix;
}

sceneObject::~sceneObject() {
    delete this->mesh;
    delete this->shader;
}