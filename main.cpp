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

void draw( unsigned int vertexShader, unsigned int fragmentShader, void ** buffers, int bufferCount) {

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

	float vertices[9] =  {-0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
	};
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

	printf(" buffer %d\n", buffer);

	void * arr[] = { &vertexShader, &fragmentShader};
	unsigned int shaderProgram = createShaderProgram(arr, 2);

	glBindVertexArray(buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(buffer);

	glViewport(0,0,500,500);
	glfwSetFramebufferSizeCallback(window, size_callback);
	glClearColor(0,0,255,1);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    	glfwSwapBuffers(window);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}