CC = g++

library:	vector.o	matrix.o
	ar rvs libglMath.a vector.o	vector.cpp	matrix.o	matrix.cpp

test: vector.o matrix.o
	$(CC) test.cpp vector.o matrix.o -o test.exe

matrix.o: matrix.cpp matrix.h vector.h
	$(CC) matrix.cpp -c

vector.o: vector.cpp
	$(CC) vector.cpp -c

clean:
	rm *.o