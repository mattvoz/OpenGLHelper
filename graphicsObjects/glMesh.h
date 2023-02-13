#ifndef __GL_MeshObject__ 
#define __GL_MeshObject__

#include <glad/glad.h>
#include "graphicsInterface.h"

typedef struct vertex {
    GLVector::vector3 position;
    GLVector::vector3 normal;
    GLVector::vector3 tangent;
    GLVector::vector2 texCoord;
}

class glMesh {
    public:
        glMesh();
        glMesh( float * vertexArray, int count );
        void computeNormals();
        GLuint returnBuffer();
        void loadBuffers();

    private:
        std::vector<vertex> vertexData;
        GLuint vertexBuffer, normalBuffer, tangentBuffer, textureBuffer;

};

#endif