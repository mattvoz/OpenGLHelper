#include "helpers.h"
#include <stdlib.h>


GLuint makeBuffer(int size, void * data) {
    GLuint buffer;
	glCreateBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 9, data,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    return buffer;
}

unsigned int createShader( char * shaderSource, char shaderType ) {
	unsigned int shader;
	if( shaderType == 0) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	} else {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	//Don't forget it's the address of your string not just the string :)
	glShaderSource(shader, 1, &shaderSource, NULL);
	return shader;
}
