#ifndef __GL__SCENE__
#define __GL__SCENE__

#include "graphicsObject.h"
#include "GLCamera.h"

class GLScene : virtual protected graphicsInterface {
    public: 
        GLScene();
        //Overide render since a scene has all the information needed for rendering
        void render();
        graphicsInterface * findChild(std::string childName);
        void setActiveCamera( GLCamera * newCam );
    protected:
        GLCamera * activeCamera;
};

#endif