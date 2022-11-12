DIR := $(CURDIR)
CC=gcc

WINDOWSHEADER = $(DIR)/OpenGL_Libraries/Windows/GLFW/include
WINDOWSLIB=$(DIR)/OpenGL_Libraries/Windows/GLFW

GLADHEADER= $(DIR)/OpenGL_Libraries/glad/include
GLADLIB = $(DIR)/OpenGL_Libraries/glad

GLADLIBWIN = $(DIR)/OpenGL_Libraries/glad/windows

#Windows mingW flags if compiling on windows use these
CFLAGS = -I$(WINDOWSHEADER) -I$(GLADHEADER)
WINFLAGS = -L$(WINDOWSLIB) -L$(GLADLIBWIN) -lglfw3 -lgdi32 -lopengl32 -lglad

#linux flags if compiling on linux try these
LINUXFLAGS = -L$(GLADLIB) -lglad -lglfw -lGL


main: main.cpp
	$(CC) main.cpp $(CFLAGS) $(WINFLAGS) -o main.exe

clean:
	rm	*.o 
