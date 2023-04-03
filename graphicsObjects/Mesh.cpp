#include "Mesh.h"
#include "helpers.h"

/**
 * Creates a new mesh to be paired with a shader.
 * Defaults to a cube
*/
Mesh::Mesh() {
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

    computeNormals();

    createBuffers();
}

void Mesh::computeNormals() {
    for( int i = 0; i < this->vertexData.size(); i+3 ) {
        GLVector::vector3 e1 = vertexData[i].position - vertexData[i+1].position;
        GLVector::vector3 e2 = vertexData[i+2].position - vertexData[i+1].position;
        GLVector::vector3 norm = e1.crossProduct( e2 );

        vertexData[i].normal = norm;
        vertexData[i+1].normal = norm;
        vertexData[i+2].normal = norm;
    }
}

void Mesh::computeTangents() {
    
}

void Mesh::createBuffers() {
    int size = vertexData.size();
    float vertexes[size * 3];
    float normals[ size * 3];
    float tangents[ size * 4];
    float texCoord[size * 2];

    for(int i = 0; i < vertexData.size(); i ++) {
        vertexes[i * 3] = vertexData[i].position.xVal();
        vertexes[i * 3 + 1] = vertexData[i].position.yVal();
        vertexes[i * 3 + 2] = vertexData[i].position.zVal();

        normals[i * 3] = vertexData[i].normal.xVal();
        normals[i * 3 + 1] = vertexData[i].normal.yVal();
        normals[i * 3 + 2] = vertexData[i].normal.zVal();
    }

    this->vertexBuffer = makeBuffer( vertexData.size() * 3, vertexes );
    this->normalBuffer = makeBuffer( vertexData.size() * 3, normals );
    this->tangentBuffer = makeBuffer( vertexData.size() * 4, tangents );
    this->textureBuffer = makeBuffer( vertexData.size() * 2, texCoord );
}

void Mesh::updateBuffers() {
    int size = vertexData.size();
    float vertexes[size * 3];
    float normals[ size * 3];
    float tangents[ size * 4];
    float texCoord[size * 2];

    for(int i = 0; i < vertexData.size(); i ++) {
        vertexes[i * 3] = vertexData[i].position.xVal();
        vertexes[i * 3 + 1] = vertexData[i].position.yVal();
        vertexes[i * 3 + 2] = vertexData[i].position.zVal();

        normals[i * 3] = vertexData[i].normal.xVal();
        normals[i * 3 + 1] = vertexData[i].normal.yVal();
        normals[i * 3 + 2] = vertexData[i].normal.zVal();
    }
}

void Mesh::applyBuffers( unsigned int shaderProgram ) {
    unsigned int positionLoc;
    //vertexes
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "a_pos");
	glEnableVertexAttribArray(positionLoc);

    //normals
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "a_normal");
	glEnableVertexAttribArray(positionLoc);

    //Tangents
    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "a_tangent");
	glEnableVertexAttribArray(positionLoc);

    //Textures
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "a_texture");
	glEnableVertexAttribArray(positionLoc);
}

Mesh::~Mesh() {
    
}