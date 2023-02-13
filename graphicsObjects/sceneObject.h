#ifndef __GL__SCENE__OBJECT__
#define __GL__SCENE__OBJECT__

#include "graphicsObject.h"
#include "shader.h"
#include "glMesh.h"

class GLSceneObject : protected graphicsInterface {
    public:
    private:
        glMesh * mesh;
        shader * shader;

};


#endif