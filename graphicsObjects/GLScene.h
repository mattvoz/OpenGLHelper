#ifndef __GL__SCENE__
#define __GL__SCENE__

#include "graphicsObject.h"
#include "GLCamera.h"

class scene : virtual protected graphicsObject {
    public: 
        void render() {
            for(int i = 0; i < children.size(); i++) {
                children[i]->object->render();
            }  
        }
    protected:
        GLCamera activeCamera;
};

#endif