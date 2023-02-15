#ifndef __GL__SCENE__OBJECT__
#define __GL__SCENE__OBJECT__

#include "graphicsInterface.h"
#include "shader.h"
#include "glMesh.h"

class glSceneObject : protected graphicsInterface {
    public:
        glSceneObject();
        glSceneObject( mesh * mesh, shader * shader );
        ~glSceneObject();
    private:
        glMesh * mesh;
        shader * shader;

};


#endif