CC = g++

library:	vec.o	mat.o
	ar rvs vec.o mat.o

mat.o: mat.cpp mat.h
	$(CC) matrix.cpp

vec.o: vec.cpp
	$(CC) vec.cpp matrix.h -c

clean:
	rm *.o