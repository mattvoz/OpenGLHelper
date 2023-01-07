#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <GL/gl.h>
#include <matrix.h>
#include "graphicsObjects/shader.h"
#include "graphicsObjects/GLCamera.h"

GLMatrix::matrix4 transform = GLMatrix::matrix4();

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
	GLCamera camera = GLCamera(30, 1.5, 0.001, 1);
	camera.translate(1,1,1);

	GLMatrix::matrix4 model = GLMatrix::matrix4();

	GLMatrix::matrix4 world = GLMatrix::matrix4();
	if(!glfwInit()) {
		return -1;
	};

	window = glfwCreateWindow(600,600, "Hello World", NULL,NULL);

	if( !window ) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
		if( !gladLoadGL() ) {
		printf("failed to load GL");
		return -1;
	}

	float vertices[] =  {
    0.0f,  0.0f, 0.0f,
    0.3f, 0.0f, 0.0f,
	0.3f,  0.2f, 0.0f,
	};

	GLuint buffer = makeBuffer(9, vertices);

	std::string vertexShaderSource = "#version 330 core\n"
    "attribute vec4 aPos;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 perspective;\n"
	"uniform mat4 transform;\n"
	"varying vec4 color;\n"
    "void main() {\n"
	"	color = vec4(aPos.xyz, 1.0);\n"
    "   gl_Position = perspective * view * model * aPos;\n"
    "}\0";

	std::string fragmentShaderSource = " #version 330 core\n"
	"out vec4 FragColor;\n"
	"varying vec4 color;"
	"void main()\n"
	"{\n"
    	"FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"FragColor.a = 1.0;\n"
	"}\0";

	shader testShader = shader(vertexShaderSource, false, fragmentShaderSource, false);

	testShader.compile();

	unsigned int shaderProgram = testShader.getProgram();

	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); 

	glBindVertexArray(buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	unsigned int positionLoc = glGetAttribLocation(shaderProgram, "aPos");
	printf("%d\n", positionLoc);
	glEnableVertexAttribArray(positionLoc);


	glBindVertexArray(buffer);

	glViewport(0,0,600,400);
	glfwSetFramebufferSizeCallback(window, size_callback);

	int x = 0;
	float z = .01;
	transform.print();
	glClearColor(.1f,0.5f,0.5f,1.0f);
	camera.getPerspective().print();
	while(!glfwWindowShouldClose(window)) {
		x = (x+1) %360;

		glClear(GL_COLOR_BUFFER_BIT);
		int loc = glGetUniformLocation( shaderProgram, "view");
		float * cameraLook = camera.getViewMatrix().toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, cameraLook);

		loc = glGetUniformLocation(shaderProgram, "model");
		float * modelMat = model.toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, modelMat);

		loc = glGetUniformLocation(shaderProgram, "perspective");
		float * projMat = camera.getPerspective().toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, projMat);

		loc = glGetUniformLocation(shaderProgram, "transform");
		float * transformMatrix = transform.toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, transformMatrix);

		glDrawArrays(GL_TRIANGLES, 0, 3);
    	glfwSwapBuffers(window);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}