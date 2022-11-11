DIR := $(CURDIR)
CC=gcc

WINDOWSHEADER = $(DIR)/OpenGL_Libraries/Windows/GLFW/include
WINDOWSLIB=$(DIR)/OpenGL_Libraries/Windows/GLFW

GLADHEADER= $(DIR)/OpenGL_Libraries/glad/include
GLADLIB = $(DIR)/OpenGL_Libraries/glad

#Windows mingW flags if compiling on windows use these
CFLAGS = -I$(WINDOWSHEADER)
WINFLAGS = -L$(WINDOWSLIB) -lglfw3 -lgdi32 -lopengl32

#linux flags if compiling on linux try these
CFLAGS=-I$(GLADHEADER)
LINUXFLAGS = -L$(GLADLIB) -lglad -lglfw -lGL


main: main.cpp
	$(CC) main.cpp $(CFLAGS) $(LINUXFLAGS) -o main.exe

clean:
	rm	*.o 
