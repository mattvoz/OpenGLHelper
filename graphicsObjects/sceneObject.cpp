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
    this->transformationMatrix.print();
    glUseProgram(NULL);
    //Render children
    for(int i = 0; i < children.size(); i++) {
        printf("rendering child");
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
    this->rotationMatrix.rotateX(x);
    this->rotationMatrix.rotateY(y);
    this->rotationMatrix.rotateZ(z);
    this->needsTransformCompute = true;
}

void sceneObject::scale( float x, float y, float z ) {
    this->scaleMatrix.set(0,0,x);
    this->scaleMatrix.set(1,1,y);
    this->scaleMatrix.set(2,2,z);
    this->needsTransformCompute = true;
}

void sceneObject::computeTransformation() {
    GLMatrix::matrix4 tranlsationMat =  GLMatrix::matrix4();
    tranlsationMat.set( 3,0,this->position.xVal() );
    tranlsationMat.set( 3,1,this->position.yVal() );
    tranlsationMat.set( 3,2,this->position.zVal() );
    this->transformationMatrix = tranlsationMat * this->rotationMatrix * this->scaleMatrix;
    this->transformationMatrix.print();
}

sceneObject::~sceneObject() {
    delete this->mesh;
    delete this->shader;
}