CC = g++

library:	vector.o	matrix.o
	ar rvs glMath.a vector.o	vector.cpp	matrix.o	matrix.cpp

matrix.o: matrix.cpp matrix.h vector.h
	$(CC) matrix.cpp -c

vector.o: vector.cpp
	$(CC) vector.cpp -c

clean:
	rm *.o