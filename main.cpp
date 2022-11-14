#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
extern "C" {
	#include "helpers.h"
}


void size_callback(GLFWwindow * window, int w, int h) {
	glViewport(0,0,w,h);
}

int main(int argc, char** argv) {
	GLFWwindow * window;

	if(!glfwInit()) {
		return -1;
	};

	window = glfwCreateWindow(500,500, "Hello World", NULL,NULL);

	if( !window ) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
		if( !gladLoadGL() ) {
		printf("failed to load GL");
		return -1;
	}

	float vertices[9] = { 0.2,-0.2,0.0,
						0.0,.2,0,
						-.2,-0.2,0};
	int n = 9;

	GLuint buffer = makeBuffer(9, vertices);

	char * vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

	char * fragmentShaderSource = " #version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
    	"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

	unsigned int vertexShader = createShader( vertexShaderSource, 0);
	unsigned int fragmentShader = createShader( fragmentShaderSource, 1);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glViewport(0,0,500,500);
	glfwSetFramebufferSizeCallback(window, size_callback);
	glClearColor(0,0,255,1);
	while(!glfwWindowShouldClose(window)) {
    	glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}