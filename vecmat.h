#ifndef __GL_VECTOR__
#define __GL_VECOTR__
namespace vector{
	class vector2 {
		public:
			vector2();
			vector2( float x);
			vector2(float x, float y);
			void normalize();
			void add( vector2 );
			float x();
			float y();
		private:
			float x;
			float y;
	};
	class vector3 {
		public:
			vector3();
			vector3(float x);
			vector3(float x, float y);
			vector3(float x, float y, float z);
			void normalize();
			void add(vector2);
			float x();
			float y();
			float z();
		private:
			float x;
			float y;
			float z;
	};
};
	
#endif