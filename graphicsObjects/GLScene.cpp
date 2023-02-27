#include "GLScene.h"

GLScene::GLScene() {

};

void GLScene::render( GLMatrix::matrix4 view, GLMatrix::matrix4 perspective ) {
    for(int i = 0; i < children.size(); i++) {
        children[i]->object->render( activeCamera.activeCamera->getViewMatrix() );
    }  
};

void GLScene::setActiveCamera( glCamera * camera ) {
    this->activeCamera = camera;
}

graphicsChildContainer * GLScene::findChild( std::string name ) {
    for( int i = 0 ; i < children.size(); i++ ) {
        if( children[i]->name.compare( name ) == 0 ) {
            return children[i];
        }
    }

    return NULL;
}