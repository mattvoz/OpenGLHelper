#ifndef __GL_CAMERA__
#define __GL_CAMERA__

#include <matrix.h>
#include "graphicsObject.h"

class GLCamera : virtual protected graphicsObject {
    public:
        GLCamera(float, float, float, float);
        GLCamera();

        void updatePerspective();
        void updateView();
        void updateNear(float);
        void updateFar(float);
        void updateFov(float);
        void updateAspect(float);

        void rotateX( float );
        void rotateY( float );
        void rotateZ( float );
        void translate( float, float, float );
        void moveTo( GLVector::vector3 );
        void lookAt( GLVector::vector3 & at );
        

        GLMatrix::matrix4& getPerspective();
        GLMatrix::matrix4& getViewMatrix();
    private:
        float fov;
        float aspect;
        float near;
        float far;
        GLMatrix::matrix4 perspectiveMatrix;
        GLMatrix::matrix4 viewMatrix;
        GLMatrix::matrix4 rotationMatrix;
        GLVector::vector3 position;
        GLVector::vector3 up;
};

#endif