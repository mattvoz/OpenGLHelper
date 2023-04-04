#ifndef __GL__SCENE__
#define __GL__SCENE__

#include "graphicsInterface.h"
#include "glCamera.h"
#include "matrix.h"
#include "vector.h"

class Scene : virtual protected graphicsInterface {
    public: 
        Scene();
        //Overide render since a scene has all the information needed for rendering
        void render(GLMatrix::matrix4 view, GLMatrix::matrix4 perspective );
        void render();
        graphicsChildContainer * findChild(std::string childName);
        void setActiveCamera( glCamera * newCam );
        ~Scene();
    protected:
        glCamera * activeCamera;
};

#endif