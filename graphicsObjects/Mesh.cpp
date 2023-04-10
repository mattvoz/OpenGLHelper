#include "Mesh.h"
#include "helpers.h"

/**
 * Creates a new mesh to be paired with a shader.
 * Defaults to a cube
*/
Mesh::Mesh() {
    float tmp[] = {
	-1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
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

    for(int i = 0; i < 36 ; i++) {
        printf("%d", i);
        vertex* x = new vertex();
        GLVector::vector3 pos = GLVector::vector3( tmp[i*3], tmp[i*3+1], tmp[i*3+2]);
        x->position = pos;
        vertexData.push_back(x);
    }

    computeNormals();

    printf("normals computed");

    createBuffers();
}

void Mesh::computeNormals() {
    for( int i = 0; i < this->vertexData.size(); i+=3 ) {
        GLVector::vector3 e1 = vertexData[i]->position - vertexData[i+1]->position;
        GLVector::vector3 e2 = vertexData[i+2]->position - vertexData[i+1]->position;
        GLVector::vector3 norm = e1.crossProduct( e2 );

        vertexData[i]->normal = norm;
        vertexData[i+1]->normal = norm;
        vertexData[i+2]->normal = norm;
    }
}

void Mesh::computeTangents() {
    
}

unsigned int Mesh::verticeCount() {
    return vertexData.size();
}

void Mesh::createBuffers() {
    int size = vertexData.size();
    float vertexes[size * 3];
    float normals[ size * 3];
    float tangents[ size * 4];
    float texCoord[size * 2];

    for(int i = 0; i < vertexData.size(); i ++) {
        vertexes[i * 3] = vertexData[i]->position.xVal();
        vertexes[i * 3 + 1] = vertexData[i]->position.yVal();
        vertexes[i * 3 + 2] = vertexData[i]->position.zVal();

        normals[i * 3] = vertexData[i]->normal.xVal();
        normals[i * 3 + 1] = vertexData[i]->normal.yVal();
        normals[i * 3 + 2] = vertexData[i]->normal.zVal();
    }

    this->vertexBuffer = makeBuffer( size * 3 * sizeof(float), vertexes );
    this->normalBuffer = makeBuffer( size * 3 * sizeof(float), normals );
    this->tangentBuffer = makeBuffer( size * 4 * sizeof(float), tangents );
    this->textureBuffer = makeBuffer( size * 2 * sizeof(float), texCoord );
}

void Mesh::updateBuffers() {
    int size = vertexData.size();
    float vertexes[size * 3];
    float normals[ size * 3];
    float tangents[ size * 4];
    float texCoord[size * 2];

    for(int i = 0; i < vertexData.size(); i ++) {
        vertexes[i * 3] = vertexData[i]->position.xVal();
        vertexes[i * 3 + 1] = vertexData[i]->position.yVal();
        vertexes[i * 3 + 2] = vertexData[i]->position.zVal();

        normals[i * 3] = vertexData[i]->normal.xVal();
        normals[i * 3 + 1] = vertexData[i]->normal.yVal();
        normals[i * 3 + 2] = vertexData[i]->normal.zVal();
    }
}

void Mesh::applyBuffers( unsigned int shaderProgram ) {
    unsigned int positionLoc;
    unsigned int vertexCount = vertexData.size();
    //vertexes
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "aPos");
    printf("position is %d\n", positionLoc);
	glEnableVertexAttribArray(positionLoc);

    //normals
    /*
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "aNormal");
    glEnableVertexAttribArray(positionLoc);
    glBindAttribLocation( shaderProgram, positionLoc, "normal");
    */

    /*
    //Tangents
    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "aTangent");
	glEnableVertexAttribArray(positionLoc);

    //Textures
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	positionLoc = glGetAttribLocation(shaderProgram, "aTexture");
	glEnableVertexAttribArray(positionLoc);
    */
}

void Mesh::printVertices() {
    for(int i = 0; i < vertexData.size(); i++) {
        printf("x: %d, y: %d, z:%d\n", vertexData[i]->position.xVal(), vertexData[i]->position.yVal(), vertexData[i]->position.zVal() );
    }
}

Mesh::~Mesh() {
    
}