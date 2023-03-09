#include "glMesh.h"

/**
 * Creates a new mesh to be paired with a shader.
 * Defaults to a cube
*/
glMesh::glMesh() {
    float tmp[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
	};

    for(int i = 0; i < 3*36 ; i+3) {
        vertex x;
        GLVector::vector3 pos = GLVector::vector3( tmp[i], tmp[i+1], tmp[i+2]);
        x.position = pos;
    }
    verticeCount = 3 * 36;

    computeNormals();

    loadBuffers();
}

void glMesh::computeNormals() {
    for( int i = 0; i < this->vertexData.size(); i+3 ) {
        GLVector::vector3 e1 = vertexData[i].position - vertexData[i+1].position;
        GLVector::vector3 e2 = vertexData[i+2].position - vertexData[i+1].position;
        GLVector::vector3 norm = e1.crossProduct( e2 );

        vertexData[i].normal = norm;
        vertexData[i+1].normal = norm;
        vertexData[i+2].normal = norm;
    }
}

void glMesh::computeTangents() {
    
}

void glMesh::loadBuffers() {
    int size = vertexData.size();
    float vertexes[size * 3];
    float normals[ size * 3];
    float tangents[ size * 3];
    float texCoord[size * 2];

    for(int i = 0; i < vertexData.size(); i ++) {
        vertexes[i * 3] = vertexData[i].position.xVal();
        vertexes[i * 3 + 1] = vertexData[i].position.yVal();
        vertexes[i * 3 + 2] = vertexData[i].position.zVal();

        normals[i * 3] = vertexData[i].normal.xVal();
        normals[i * 3 + 1] = vertexData[i].normal.yVal();
        normals[i * 3 + 2] = vertexData[i].normal.zVal();
    }

    glCreateBuffers(1,&vertexBuffer);
    glCreateBuffers(1,&normalBuffer);
    glCreateBuffers(1,&tangentBuffer);
    glCreateBuffers(1,&textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertexes,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}