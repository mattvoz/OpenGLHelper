#ifndef __GL_CAMERA__
#define __GL_CAMERA__

#include <matrix.h>
#include "graphicsObject.h"

class GLCamera : virtual protected graphicsInterface {
    public:
        GLCamera(float fov, float aspectRatio);
        GLCamera();

        void updatePerspective();
        void updateView();
        void updateNear(float);
        void updateFar(float);
        void updateFov(float);
        void updateAspect(float);

        void rotateX( float degrees );
        void rotateY( float degrees );
        void rotateZ( float degrees );
        void translate( float x, float y, float z);
        void moveTo( GLVector::vector3 );
        void lookAt( GLVector::vector3 & at );
        

        GLMatrix::matrix4& getPerspective();
        GLMatrix::matrix4& getViewMatrix();
    private:
        float fov;
        float aspect;
        float near;
        float far;
        bool needsUpdate;
        GLMatrix::matrix4 perspectiveMatrix;
        GLMatrix::matrix4 viewMatrix;
        GLVector::vector3 up;
};

#endif