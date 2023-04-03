#ifndef __GL__SCENE__OBJECT__
#define __GL__SCENE__OBJECT__

#include "graphicsInterface.h"
#include "shader.h"
#include "glMesh.h"

class glSceneObject : protected virtual graphicsInterface {
    public:
        glSceneObject();
        glSceneObject( glMesh * mesh, shader * shader );
        void setMesh( glMesh * mesh );
        void setShader( shader * shader );
        ~glSceneObject();
    private:
        glMesh * mesh;
        shader * shader;

};


#endif