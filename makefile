DIR := $(CURDIR)
CC=g++

WINDOWSHEADER = $(DIR)/OpenGL_Libraries/GLFW/include
WINDOWSLIB=$(DIR)/OpenGL_Libraries/GLFW

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

executable:	main.o	helpers.o	glCamera.o Mesh.o	Shader.o	sceneObject.o	Scene.o
	$(CC) *.o  $(CFLAGS) $(LIBS) -o main.exe

main.o: main.cpp
	$(CC) main.cpp	$(CFLAGS)	$(LIBS) -c

#since helpers is a C program hard code in using gcc to compile
helpers.o: ./graphicsObjects/helpers.cpp	./graphicsObjects/helpers.h
	gcc ./graphicsObjects/helpers.cpp $(CFLAGS) $(LIBS) -c

glCamera.o:	graphicsObjects/glCamera.cpp	graphicsObjects/glCamera.h
	$(CC) graphicsObjects/glCamera.cpp $(CFLAGS) $(LIBS) -c

Scene.o: graphicsObjects/Scene.cpp graphicsObjects/Scene.h
	$(CC) graphicsObjects/Scene.cpp $(CFLAGS) $(LIBS) -c

sceneObject.o:	graphicsObjects/sceneObject.h	graphicsObjects/sceneObject.cpp
	$(CC)	graphicsObjects/sceneObject.cpp	$(CFLAGS) $(LIBS) -c

Shader.o:	graphicsObjects/Shader.cpp	graphicsObjects/Shader.h
	$(CC) graphicsObjects/Shader.cpp $(CFLAGS) $(LIBS) -c

Mesh.o:	graphicsObjects/Mesh.cpp graphicsObjects/Mesh.h
	$(CC) graphicsObjects/Mesh.cpp  $(CFLAGS) $(LIBS) -c

clean:
	rm	*.o 
