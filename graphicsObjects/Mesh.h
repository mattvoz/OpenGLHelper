#ifndef __GL_MeshObject__ 
#define __GL_MeshObject__

#include <glad/glad.h>
#include <vector.h>
#include "graphicsInterface.h"

typedef struct vertex {
    GLVector::vector3 position;
    GLVector::vector3 normal;
    GLVector::vector3 tangent;
    GLVector::vector2 texCoord;
} vertex;

typedef struct vertex2D {
    GLVector::vector2 position;
} vertex2D;

class Mesh {
    public:
        Mesh();
        Mesh( float * vertexArray, int count );
        void addNormals( float * normals, unsigned int count);
        void addTextureCoords( float * coords, unsigned int count );
        void computeNormals();
        void computeTangents();
        void createBuffers();
        void applyBuffers( unsigned int shaderProgram );
        unsigned int verticeCount();
        void printVertices();
        ~Mesh();

    private:
        void updateBuffers();
        std::vector<vertex*> vertexData = std::vector<vertex*>();
        GLuint vertexBuffer, normalBuffer, tangentBuffer, textureBuffer;
        bool vertexNeedsUpdate, normalNeedsUpdate, tangentNeedsUpdate, textureNeedsUpdate;

};

class Mesh2D{
    public:
        Mesh2D();
        Mesh2D( float * vertexArray, int count );
    private:
        void updateBuffers();
        bool verticesNeedUpdate;
        std::vector<vertex2D*> vertexData = std::vector<vertex2D *>();
};

#endif