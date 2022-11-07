DIR := $(CURDIR)
WINDOWSHEADER = $(CURDIR)/OpenGL_Libraries/Windows/GLFW/include
WINDOWSLIB=$(CURDIR)/OpenGL_Libraries/Windows/GLFW

#Windows mingW flags if compiling on windows use these
CFLAGS = -I$(WINDOWSHEADER)
WINFLAGS = -L$(WINDOWSLIB) -lglfw3 -lgdi32 -lopengl32

#linux flags if compiling on linux try these
LFLAGS = -lglfw -lGL


main: main.cpp
	gcc main.cpp $(CFLAGS) $(LFLAGS) -o main.exe
clean:
	rm	*.o 
