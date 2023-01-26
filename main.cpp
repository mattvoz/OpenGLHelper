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

int width = 1920;
int height = 1080;

GLCamera camera;

extern "C" {
	#include "helpers.h"
}


void size_callback(GLFWwindow * window, int w, int h) {
	width = w;
	height = h;

	camera.updateAspect(width/height);
	camera.updatePerspective();

	glViewport(0,0,width,height);
}

void draw( unsigned int vertexShader, unsigned int fragmentShader, void ** buffers, int bufferCount) {

}

int main(int argc, char** argv) {
	GLFWwindow * window;
	camera = GLCamera(60, width/height);
	GLVector::vector3 origin = GLVector::vector3(0,0,0);
	camera.moveTo(GLVector::vector3(1,3,3));
	camera.lookAt(origin);

	GLMatrix::matrix4 model = GLMatrix::matrix4();

	GLMatrix::matrix4 world = GLMatrix::matrix4();
	if(!glfwInit()) {
		return -1;
	};

	window = glfwCreateWindow(1000,1000, "Hello World", NULL,NULL);

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

	GLuint buffer = makeBuffer(12*3, vertices);

	std::string vertexShaderSource = "#version 330 core\n"
    "attribute vec3 aPos;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"varying vec4 color;\n"
    "void main() {\n"
	"	color = vec4(aPos.xyz, 1.0);\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
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

	shaderVariables test = shaderVariables();

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

	glViewport(0,0,1000,1000);
	glfwSetFramebufferSizeCallback(window, size_callback);

	int x = 0;
	float z = .01;
	glClearColor(.1f,0.5f,0.5f,1.0f);

	camera.getViewMatrix().print();
	camera.getPerspective().print();

	test.addVariable( mat4, "projection", &camera.getPerspective());
	test.addVariable(mat4, "view", &camera.getViewMatrix());
	test.addVariable(mat4, "model", &model);
	
	while(!glfwWindowShouldClose(window)) {
		x = (x+1) %360;
		glClear(GL_COLOR_BUFFER_BIT);
		test.applyVariables(shaderProgram);
		/*
		GLint loc = glGetUniformLocation( shaderProgram, "view");
		float * cameraLook = camera.getViewMatrix().toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, cameraLook);

		loc = glGetUniformLocation(shaderProgram, "model");
		float * modelMat = model.toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, modelMat);

		loc = glGetUniformLocation(shaderProgram, "projection");
		float * projMat = camera.getPerspective().toArray();
		glUniformMatrix4fv(loc,1,GL_FALSE, projMat);
		*/

		glDrawArrays(GL_TRIANGLES, 0, 12*3);
    	glfwSwapBuffers(window);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}