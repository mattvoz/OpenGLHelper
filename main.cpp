#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <GL/gl.h>
#include <matrix.h>
#include "graphicsObjects/Shader.h"
#include "graphicsObjects/GLCamera.h"
#include "graphicsObjects/helpers.h"
#include "graphicsObjects/sceneObject.h"
#include "graphicsObjects/Scene.h"

GLMatrix::matrix4 transform = GLMatrix::matrix4();

float width = 1920;
float height = 1080;

glCamera camera;

void size_callback(GLFWwindow * window, int w, int h) {
	width = w;
	height = h;

	camera.updateAspect(width/height);
	camera.updatePerspective();

	glViewport(0,0,width,height);
}

int main(int argc, char** argv) {
	float test = 0.00000001f;
	double testTwo = 0.00000001;
	GLFWwindow * window;
	camera = glCamera(90, width/height);
	GLVector::vector3 origin = GLVector::vector3(0,0,0);
	camera.moveTo(GLVector::vector3(0,10,0));
	camera.lookAt(origin);

	if(!glfwInit()) {
		return -1;
	};

	window = glfwCreateWindow(width,height, "Hello World", NULL,NULL);

	if( !window ) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
		if( !gladLoadGL() ) {
		printf("failed to load GL");
		return -1;
	}

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

	std::string fragmentShaderSourceBlue = " #version 330 core\n"
	"out vec4 FragColor;\n"
	"varying vec4 color;"
	"void main()\n"
	"{\n"
    	"FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
		"FragColor.a = 1.0;\n"
	"}\0";

	Scene * testScene = new Scene();

	Mesh testMesh = Mesh();

	sceneObject testObject = sceneObject();

	sceneObject testChild = sceneObject();

	testChild.getShader()->setFragmentShader( fragmentShaderSourceBlue, false );

	graphicsChildContainer child = { &testChild, "test" };

	testObject.addChild(&child);

	testChild.translate(5,0,-1);

	glEnable(GL_DEPTH_TEST);

	glViewport(0,0,width,height);
	glfwSetFramebufferSizeCallback(window, size_callback);

	int x = 0;
	float z = .01;
	glClearColor(0.10f,1.0f,1.0f,0.0f);

	
	while(!glfwWindowShouldClose(window)) {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		GLMatrix::matrix4 world = GLMatrix::matrix4();
		testObject.render(world, camera.getViewMatrix(), camera.getPerspective() );
		z += 1;

		testObject.rotate(0,z,0);
		testChild.rotate(z,0,0);

        /*
		x = (x-1) %360;
		glClear(GL_COLOR_BUFFER_BIT);
		test.applyVariables(shaderProgram);
		model.rotateX(x);
		*/

		//glDrawArrays(GL_TRIANGLES, 0, 36*3);
    	glfwSwapBuffers(window);
    	glfwPollEvents();
	}

	glfwTerminate();
	exit(1);
}