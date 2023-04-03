#ifndef __GL__SCENE__OBJECT__
#define __GL__SCENE__OBJECT__

#include "graphicsInterface.h"
#include "Shader.h"
#include "Mesh.h"

class sceneObject : protected virtual graphicsInterface {
    public:
        sceneObject();
        sceneObject( Mesh * mesh, Shader * shader );
        virtual void render( GLMatrix::matrix4 & world );
        void setMesh( Mesh * mesh );
        void setShader( Shader * shader );
        ~sceneObject();
    private:
        Mesh * mesh;
        Shader * shader;

};


#endif