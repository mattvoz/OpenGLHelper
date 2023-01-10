#ifndef __GL_VECTOR__
#define __GL_VECOTR__

class mat2;
class mat3;
class mat4;

namespace GLVector{
	class vector2 {
		public:
			//Constructors Destructors
			vector2();
			vector2( float x);
			vector2(float x, float y);
			~ vector2();
			
			//Operators
			vector2 operator * (const vector2 &);
			vector2 operator * ( const mat2 & );
			vector2 operator * (float);
			vector2 operator + (const vector2 &);
			vector2 operator - (const vector2 &);

			//Methods
			vector2 normalize();
			float dot( vector2 &);
			void scale( float );
			float length();

			float xVal();
			float yVal();
			private:
			float x;
			float y;
	};
	
	class vector3 {
		public:
			//Constructors Destructors
			vector3();
			vector3(float);
			vector3(float, float);
			vector3(float, float, float);
			vector3(vector2, float);
			~ vector3();

			//Operators
			vector3 operator *( const vector3 & );
			vector3 operator *(float);
			vector3 operator + ( const vector3 & );
			vector3 operator - ( const vector3 & );
			void operator = (const vector3 &);

			//methods
			vector3 normalize();
			vector3 crossProduct( const vector3 &);
			float dot( const vector3 &);
			float scaleX( float );
			float scaleY(float);
			float scaleZ(float);
			float length();

			float xVal();
			float yVal();
			float zVal();
		private:
			float x;
			float y;
			float z;
	};

	class vector4 {
		public:
			//Constructors Destructors
			vector4();
			vector4(float x);
			vector4(float x, float y);
			vector4(float x, float y, float z);
			vector4(float x, float y, float z, float w);
			vector4( vector3, float);
			~vector4();

			//Operators
			vector4  operator *( const vector4 & );
			vector4 operator * ( const mat4 & );
			vector4 operator* (float);
			vector4 operator + ( const vector4 & );
			vector4 operator - (const vector4 & );

			//Methods
			vector4 dot( vector4 & );
			void applyMatrix( mat4& );
			void scaleX( float );
			void scaleY(float);
			void scaleZ(float);
			float length();
			vector4 normalize();
			vector4 lerp( vector4, float);

			//getters
			float xVal();
			float yVal();
			float zVal();
			float wVal();
		private:
			float x;
			float y;
			float z;
			float w;
			friend class vector3;
	};
}
#endif
