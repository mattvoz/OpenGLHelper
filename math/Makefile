CC = g++

library:	vec.o	mat.o
	ar rvs vec.o mat.o

vec.o: vec.cpp
	$(CC) vec.cpp -c

clean:
	rm *.o