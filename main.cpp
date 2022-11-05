#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <process.h>

void size_callback(GLFWwindow * window, int w, int h) {
	glViewport(0,0,w,h);
}

int main(int argc, char** argv) {
	GLFWwindow * window;

	if(!glfwInit()) {
		return -1;
	}

	window = glfwCreateWindow(500,500, "Hello World", NULL,NULL);

	if( !window ) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glViewport(0,0,500,500);
	glfwSetFramebufferSizeCallback(window, size_callback);  
	while(!glfwWindowShouldClose(window)) {
    	glfwSwapBuffers(window);
    	glfwPollEvents();    
	}

	glfwTerminate();
	exit(1);
}