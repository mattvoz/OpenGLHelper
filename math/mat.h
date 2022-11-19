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
		private:
			float row1[2];
			float row2[2];
	};
}

#endif