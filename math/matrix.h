#ifndef __GL_matrixRIX__
#define __GL_matrixRIX__

class vec2;
class vec3;
class vec4;
namespace GLMatrix {
	class matrix2 {
		public:
			matrix2();
			matrix2( float [4]);
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
			matrix3( float[9] );
			matrix3( float * );
			~matrix3();

		//Operators
			matrix3 operator * (matrix3 &);

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
			matrix4(float[16]);
			matrix4( float * );
			~matrix4();

		//Operators
			matrix4 operator * ( matrix4 & );

		
		//Methods
			void transpose();
			float * toArray();
			float get( int , int);
			void translation(float, float, float);
			void rotateX( int );
			void rotateY( int );
			void rotateZ( int );
			void scale(int , int);
		private:
			float values[16];
	};
}


#endif