#ifndef __GL_HELPERS__
#define __GL_HELPERS__
#include <glad/glad.h>

GLuint makeBuffer( int, void *);

unsigned int createShader( const char *, char );

unsigned int createShaderProgram( unsigned int **, int );



#endif