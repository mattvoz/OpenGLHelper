#include "GLScene.h"

GLScene::GLScene() {

};

void GLScene::render() {
    for(int i = 0; i < children.size(); i++) {
        children[i]->object->render( activeCamera->getPerspective(), activeCamera->getViewMatrix() );
    }  
};

void GLScene::setActiveCamera( GLCamera * camera ) {
    this->activeCamera = camera;
}