DIR := $(CURDIR)
CC=g++

WINDOWSHEADER = $(DIR)/OpenGL_Libraries/Windows/GLFW/include
WINDOWSLIB=$(DIR)/OpenGL_Libraries/Windows/GLFW

GLADHEADER= $(DIR)/OpenGL_Libraries/glad/include
GLADLIB = $(DIR)/OpenGL_Libraries/glad

GLADLIBWIN = $(DIR)/OpenGL_Libraries/glad/windows

MATHHEADER = $(DIR)/math
MATHLIB = $(DIR)/math

#Windows mingW flags if compiling on windows use these
CFLAGS = -I$(WINDOWSHEADER) -I$(GLADHEADER) -I$(MATHHEADER)
ifeq ($(OS),Windows_NT) 
	LIBS = -L$(WINDOWSLIB) -L$(GLADLIBWIN) -L$(MATHLIB) -lglfw3 -lgdi32 -lopengl32 -lglad	-lglMath

else
#linux flags if compiling on linux try these
	LIBS = -L$(GLADLIB) -L$(MATHLIB) -lglad -lglfw -lGL -lglMath	-lglMath
endif

executable:	main.o	helpers.o	shader.o	GLCamera.o
	$(CC) main.o helpers.o	shader.o	GLCamera.o  $(CFLAGS) $(LIBS) -o main.exe

main.o: main.cpp	helpers.h
	$(CC) main.cpp	$(CFLAGS)	$(LIBS) -c

#since helpers is a C program hard code in using gcc to compile
helpers.o: helpers.c	helpers.h
	gcc helpers.c $(CFLAGS) $(LIBS) -c

GLCamera.o:	graphicsObjects/GLCamera.cpp	graphicsObjects/GLCamera.h
	$(CC) graphicsObjects/GLCamera.cpp $(CFLAGS) $(LIBS) -c

shader.o:	graphicsObjects/shader.cpp	graphicsObjects/shader.h
	$(CC) graphicsObjects/shader.cpp $(CFLAGS) $(LIBS) -c

clean:
	rm	*.o 
