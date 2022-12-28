#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <GL/gl.h>
#include <matrix.h>
#include "graphicsObjects/shader.h"

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

	GLMatrix::matrix4 camera = GLMatrix::matrix4();

	GLMatrix::matrix4 model = GLMatrix::matrix4();

	GLMatrix::matrix4 world = GLMatrix::matrix4();

	camera.print();
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
    "attribute vec3 aPos;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"uniform mat4 transform;\n"
	"varying vec4 color;\n"
    "void main() {\n"
	"	color = vec4(aPos.xyz, 1.0);\n"
    "   gl_Position = transform * vec4(aPos,1.0);\n"
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

	glViewport(0,0,600,600);
	glfwSetFramebufferSizeCallback(window, size_callback);

	GLMatrix::matrix4 test = GLMatrix::matrix4();
	int x = 30;
	transform.rotateZ(x);
	transform.print();
	while(!glfwWindowShouldClose(window)) {
		x ++;
		glClear(GL_COLOR_BUFFER_BIT);
		int loc = glGetUniformLocation( shaderProgram, "view");
		float * cameraLook = camera.toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, cameraLook);

		loc = glGetUniformLocation(shaderProgram, "model");
		float * modelMat = model.toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, modelMat);

		loc = glGetUniformLocation(shaderProgram, "projection");
		float * projMat = world.toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, projMat);

		loc = glGetUniformLocation(shaderProgram, "transform");
		float * transformMatrix = transform.toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, transformMatrix);

		delete modelMat;
		delete cameraLook;
		delete projMat;
		delete transformMatrix;
		glDrawArrays(GL_TRIANGLES, 0, 3);
    	glfwSwapBuffers(window);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}