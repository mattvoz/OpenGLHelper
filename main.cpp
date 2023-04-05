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

int width = 1920;
int height = 1080;

glCamera camera;


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
	camera = glCamera(60, width/height);
	GLVector::vector3 origin = GLVector::vector3(0,0,0);
	camera.moveTo(GLVector::vector3(1,3,3));
	camera.lookAt(origin);

	GLMatrix::matrix4 model = GLMatrix::matrix4();

	GLMatrix::matrix4 world = GLMatrix::matrix4();
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

	GLuint buffer = makeBuffer(3 * 36, vertices);

	Shader testShader = Shader(vertexShaderSource, false, fragmentShaderSource, false);

	shaderVariables test = shaderVariables();

	testShader.compile();

	Scene * testScene = new Scene();

	Mesh testMesh = Mesh();

	sceneObject testObject = sceneObject();

	unsigned int shaderProgram = testShader.getProgram();

	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); 

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	unsigned int positionLoc = glGetAttribLocation(shaderProgram, "pos");
	printf("vertex location is: %d\n", positionLoc);
	glEnableVertexAttribArray(positionLoc);

	glViewport(0,0,width,height);
	glfwSetFramebufferSizeCallback(window, size_callback);

	int x = 0;
	float z = .01;
	glClearColor(.1f,0.5f,0.5f,1.0f);

	test.addVariable( mat4, "projection", &camera.getPerspective());
	test.addVariable(mat4, "view", &camera.getViewMatrix());
	test.addVariable(mat4, "model", &model);

	testShader.setVariables( &test );
	testObject.setShader( & testShader );
	
	while(!glfwWindowShouldClose(window)) {
		glClear( GL_COLOR_BUFFER_BIT );
		GLMatrix::matrix4 world = GLMatrix::matrix4();
		testObject.render(world);

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