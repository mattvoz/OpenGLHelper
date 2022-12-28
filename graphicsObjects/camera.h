#ifndef __GL_CAMERA__
#define __GL_CAMERA__

#include "./math/matrix.h"
#include "graphicsObject.h"

class camera : private graphicsObject {
    public:
        camera(float, float, float, float);
        camera();

        void updatePerspective();
        void updateNear(float);
        void updateFar(float);
        void updateFov(float);
        void updateAspect(float);
    private:
        float fov;
        float aspect;
        float zNear;
        float zFar;

};

#endif