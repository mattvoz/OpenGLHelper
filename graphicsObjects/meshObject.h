#ifndef __GL_MeshObject__ 
#define __GL_MeshObject__

#include "graphicsObject.h"

class glMesh : virtual protected graphicsObject {
    public:
        void addChild();


    private:
        float * vertices;
        int verticeCount;
        float * normals;
        int normalCount;
        float * tangents;
        int tangentCount;

};

#endif