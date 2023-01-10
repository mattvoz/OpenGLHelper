#ifndef __GL_MATRIX__
#define __GL_MATRIX__

float toRadians( float );
namespace GLVector{
	class vector2;
	class vector3;
	class vector4;
}

namespace GLMatrix {
	class matrix2 {
		public:
			matrix2();
			matrix2( float *);
			matrix2( float, float, float, float);
			~matrix2();

		//Operators
			matrix2 operator * ( const matrix2 & );

		//Methods
			void transpose();
			float* toArray();
		private:
			float values[4];
	};

	class matrix3 {
		public:
			matrix3();
			matrix3( float * );
			~matrix3();

		//Operators
			matrix3 operator * (matrix3 &);
			GLVector::vector3 operator * (GLVector::vector3 &);

		//Methods
			void transpose();
			float * toArray();
			float get(int, int);
			void translation(float, float);
			void rotation( int );
			void scale(int , int);
			void scale( float, float );
			void makeIdentity();
		private:
			float values[9];

	};

	class matrix4 {
		public:
			matrix4();
			matrix4( float * );
			~matrix4();

		//Operators
			matrix4 operator * ( matrix4 & );
			matrix4 operator - ( matrix4 & );
			matrix4 operator + ( matrix4 & );
			GLVector::vector4 operator * (GLVector::vector4 &);
		
		//Methods
			void transpose();
			float get( int , int);
			float * toArray();
			void makeIdentity();
			void translation(float, float, float);
			void makeTranslation(float,float,float);
			void rotateX( float );
			void rotateY( float );
			void rotateZ( float );
			void scale( float, float, float );
			void makePerspective(float, float, float, float, float, float);
			matrix4 lookAt( GLVector::vector3 &, GLVector::vector3 &, GLVector::vector3 &);
			void print();
		private:
			float values[16];
	};
}


#endif