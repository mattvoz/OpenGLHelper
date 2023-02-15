#ifndef __GL__SCENE__
#define __GL__SCENE__

#include "graphicsObject.h"
#include "glCamera.h"

class GLScene : virtual protected graphicsInterface {
    public: 
        GLScene();
        //Overide render since a scene has all the information needed for rendering
        void render();
        graphicsChildContainer * findChild(std::string childName);
        void setActiveCamera( glCamera * newCam );
    protected:
        glCamera * activeCamera;
};

#endif