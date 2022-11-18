#ifndef __GL_VECTOR__
#define __GL_VECOTR__
namespace GLvector{
	class vector2 {
		public:
			vector2();
			vector2( float x);
			vector2(float x, float y);
			void normalize();
			void add( vector2 );
			vector2 operator * ( const vector2 & );
			vector2 dot( vector2 );
			float length();
			float x();
			float y();
			~ vector2();
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
			vector3 operator *( const vector3 & vec );
			float length();
			~vector3();
			float x();
			float y();
			float z();
		private:
			float x;
			float y;
			float z;
	};
	class vector4 {
		public:
			vector4();
			vector4(float x);
			vector4(float x, float y);
			vector4(float x, float y, float z);
			vector4(float x, float y, float z, float a);
			void normalize();
			vector4  operator *( const vector4 & vec);
			vector4 dot( vector4 );
			float x();
			float y();
			float z();
			float a();
			~vector4;
		private:
			float x;
			float y;
			float z;
			float a;
			friend class vector3;
	};
};
	
#endif

#ifndef __GL_MATRIX__
#define __GL_MATRIX__

#endif