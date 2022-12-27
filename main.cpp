#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <matrix.h>

extern "C" {
	#include "helpers.h"
}


void size_callback(GLFWwindow * window, int w, int h) {
	glViewport(0,0,w,h);
}

void draw( unsigned int vertexShader, unsigned int fragmentShader, void ** buffers, int bufferCount) {

}

int main(int argc, char** argv) {
	GLFWwindow * window;

	GLMatrix::matrix4 * camera = new GLMatrix::matrix4();

	GLMatrix::matrix4 rot = GLMatrix::matrix4();

	rot.rotateY(60);

	*camera = *camera * rot;
	camera->print();

	if(!glfwInit()) {
		return -1;
	};

	window = glfwCreateWindow(1920,1080, "Hello World", NULL,NULL);

	if( !window ) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
		if( !gladLoadGL() ) {
		printf("failed to load GL");
		return -1;
	}

	float vertices[9] =  {-0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
	};
	int n = 9;

	GLuint buffer = makeBuffer(9, vertices);

	char * vertexShaderSource = "#version 330 core\n"
    "attribute vec4 aPos;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"varying vec4 color;\n"
    "void main()\n"
    "{\n"
	"	color = aPos;\n"
    "   gl_Position = view * aPos;\n"
    "}\0";

	char * fragmentShaderSource = " #version 330 core\n"
	"out vec4 FragColor;\n"
	"varying vec4 color;"
	"void main()\n"
	"{\n"
    	"FragColor = color + 1.0;\n"
		"FragColor.a = 1.0;\n"
	"}\0";

	unsigned int vertexShader = createShader( vertexShaderSource, 0);
	unsigned int fragmentShader = createShader( fragmentShaderSource, 1);

	printf(" buffer %d\n", buffer);

	unsigned int * arr[] = { &vertexShader, &fragmentShader};
	unsigned int shaderProgram = createShaderProgram(arr, 2);

	glBindVertexArray(buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); 

	glUseProgram(shaderProgram);
	glBindVertexArray(buffer);

	glViewport(0,0,1920,1080);
	glfwSetFramebufferSizeCallback(window, size_callback);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		int loc = glGetUniformLocation( shaderProgram, "view");
		glUniformMatrix4fv(loc,1,false, camera->toArray());
		glDrawArrays(GL_TRIANGLES, 0, 3);
    	glfwSwapBuffers(window);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}