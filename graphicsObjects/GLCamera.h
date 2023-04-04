#ifndef __GL_CAMERA__
#define __GL_CAMERA__

#include <matrix.h>
#include "graphicsInterface.h"

class glCamera : virtual protected graphicsInterface {
    public:
        glCamera(float fov, float aspectRatio);
        glCamera();

        void updatePerspective();
        void updateView();
        void updateNear(float);
        void updateFar(float);
        void updateFov(float);
        void updateAspect(float);
        void updateLocalWorldMatrix();

        void rotateX( float degrees );
        void rotateY( float degrees );
        void rotateZ( float degrees );
        void translate( float x, float y, float z);
        void moveTo( GLVector::vector3 );
        void lookAt( GLVector::vector3 & at );
        virtual void render( GLMatrix::matrix4 & world );
        

        GLMatrix::matrix4& getPerspective();
        GLMatrix::matrix4& getViewMatrix();
        GLMatrix::matrix4& getWolrdMatrix();
    private:
        float fov;
        float aspect;
        float near;
        float far;
        bool needsUpdate;
        bool worldNeedsUpdate;
        GLMatrix::matrix4 perspectiveMatrix;
        GLMatrix::matrix4 viewMatrix;
        GLVector::vector3 up;

        GLMatrix::matrix4 localWorldMatrix;
};

#endif