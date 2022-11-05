DIR := $(CURDIR)
WINDOWSHEADER = $(CURDIR)/OpenGL_Libraries/Windows/GLFW/include
WINDOWSLIB=$(CURDIR)/OpenGL_Libraries/Windows/GLFW

CFLAGS = -I$(WINDOWSHEADER)
LDFLAGS = -L$(WINDOWSLIB) -lglfw3 -lgdi32 -lopengl32

main: main.cpp
	gcc main.cpp $(CFLAGS) $(LDFLAGS) -o main.exe
clean:
	rm	*.o 
