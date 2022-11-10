#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>


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
	
	glViewport(0,0,500,500);
	glfwSetFramebufferSizeCallback(window, size_callback);
	glClearColor(0,0,255,1);
	while(!glfwWindowShouldClose(window)) {
    	glfwSwapBuffers(window);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}