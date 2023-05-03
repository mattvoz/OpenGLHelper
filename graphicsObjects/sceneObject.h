#ifndef __GL__SCENE__OBJECT__
#define __GL__SCENE__OBJECT__

#include "graphicsInterface.h"
#include "Shader.h"
#include "Mesh.h"

class sceneObject : protected virtual graphicsInterface {
    public:
        sceneObject();
        sceneObject( Mesh * mesh, Shader * shader );
        virtual void render( GLMatrix::matrix4 & world, GLMatrix::matrix4 & view, GLMatrix::matrix4 & perspective );
        void setMesh( Mesh * mesh );
        void setShader( Shader * shader );
        void rotate(float x, float y, float z);
        ~sceneObject();
    private:
        void computeTransformation();
        Mesh * mesh;
        Shader * shader;
        bool needsTransformCompute = false;
        GLMatrix::matrix4 rotation;
        GLMatrix::matrix4 scale;
        GLVector::vector3 position;
        GLMatrix::matrix4 transformationMatrix;

};


#endif