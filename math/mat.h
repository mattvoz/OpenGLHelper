#ifndef __GL_MATRIX__
#define __GL_MATRIX__

class vec2;
class vec3;
class vec4;
namespace GLMatrix {
	class mat2 {
		public:
			mat2();
			mat2( float [4]);
			mat2( float *);
			mat2( float, float, float, float);
			~mat2();

			//Methods
			void transpose();
		private:
			float row1[2];
			float row2[2];
	};

	class mat3 {
		public:
			mat3();
			mat3( float[9] );
			mat3( float * );
			~mat3();

			//methods
			void transpose();
		private:
			float row1[3];
			float row2[3];
			float row3[3];

	};

	class mat4 {
		public:
			mat4();
			mat4(float[16]);
			mat4( float * );
			~mat4();
		
		//Methods
			void transpose();
		private:
			float row1[4];
			float row2[4];
			float row3[4];
			float row4[4];
	};
}


#endif