DIR := $(CURDIR)
CC=gcc

WINDOWSHEADER = $(DIR)/OpenGL_Libraries/Windows/GLFW/include
WINDOWSLIB=$(DIR)/OpenGL_Libraries/Windows/GLFW

GLADHEADER= $(DIR)/OpenGL_Libraries/glad/include
GLADLIB = $(DIR)/OpenGL_Libraries/glad

GLADLIBWIN = $(DIR)/OpenGL_Libraries/glad/windows

#Windows mingW flags if compiling on windows use these
CFLAGS = -I$(WINDOWSHEADER) -I$(GLADHEADER)
ifeq ($(OS),Windows_NT) 
	LIBS = -L$(WINDOWSLIB) -L$(GLADLIBWIN) -lglfw3 -lgdi32 -lopengl32 -lglad

else
#linux flags if compiling on linux try these
	LIBS = LINUXFLAGS = -L$(GLADLIB) -lglad -lglfw -lGL
endif

executable:	main.o	helpers.o
	$(CC) main.o helpers.o  $(CFLAGS) $(LIBS) -o main.exe

main.o: main.cpp
	$(CC) main.cpp	$(CFLAGS)	$(LIBS) -c

helpers.o: helpers.c	helpers.h
	$(CC) helpers.c $(CFLAGS) $(LIBS) -c

clean:
	rm	*.o 
