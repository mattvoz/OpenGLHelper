#include "Scene.h"

Scene::Scene() {
    activeCamera = new glCamera();
};

void Scene::render( GLMatrix::matrix4 & view, GLMatrix::matrix4 & perspective ) {
    GLMatrix::matrix4 world = GLMatrix::matrix4();
    for(int i = 0; i < children.size(); i++) {
        children[i]->object->render( world, view, perspective );
    }  
};

void Scene::setActiveCamera( glCamera * camera ) {
    this->activeCamera = camera;
}

graphicsChildContainer * Scene::findChild( std::string name ) {
    for( int i = 0 ; i < children.size(); i++ ) {
        if( children[i]->name.compare( name ) == 0 ) {
            return children[i];
        }
    }

    return NULL;
}

Scene::~Scene() {
    delete activeCamera;
}