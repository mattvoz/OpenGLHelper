#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * Creates a buffer that reads size data points from a void * usually a float array data.
 * 
 * @param size int the amount of data points being passed.
 * @param data void * the data being passed into the  buffer. 
*/
GLuint makeBuffer(int size, void * data) {
    GLuint buffer;
	glCreateBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    return buffer;
}

/**
 * Creates a shader in openGL and returns the handle for that shader :).
**/
unsigned int createShader( char * shaderSource, char shaderType ) {
	unsigned int shader;
	if( shaderType == 0) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	} else {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	//Don't forget it's the address of your string not just the string :)
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	return shader;
}

/**
 * This function will generate a shader program based on shaders passed to it in a void * array[] please pass the pointers to the 
 * shaders not the shaders number value :), it also needs the size to process the shaders;
 * 
 * @param void** shaders an arary of shader pointers to be passed.
 * @param int shaderCount the amount of shaders you have.
 * 
**/
unsigned int createShaderProgram( unsigned int ** shaders, int shaderCount ) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	for(int i = 0; i < shaderCount; i++) {
		glAttachShader(shaderProgram, *(GLuint*)shaders[i]);
	}
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	return shaderProgram;
}
