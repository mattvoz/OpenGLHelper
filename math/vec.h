#ifndef __GL_VECTOR__
#define __GL_VECOTR__

class mat2;
class mat3;
class mat4;

namespace GLVector{
	class vector2 {
		public:
			vector2();
			vector2( float x);
			vector2(float x, float y);
			~ vector2();

			vector2 normalize();
			void add( vector2 & );
			vector2 operator * ( const vector2 & );
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
			//Constructors 
			vector3();
			vector3(float x);
			vector3(float x, float y);
			vector3(float x, float y, float z);
			~ vector3();

			vector3 normalize();
			void add( vector3 & );
			vector3 operator *( const vector3 & vec );
			vector3 applyMatrix( mat3 & );
			float scale( float );
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
			//Constructors
			vector4();
			vector4(float x);
			vector4(float x, float y);
			vector4(float x, float y, float z);
			vector4(float x, float y, float z, float a);
			~vector4();

			//Methods
			void normalize();
			vector4  operator *( const vector4 & vec);
			vector4 dot( vector4 & );
			void applyMatrix( mat4& );
			float scale( float );
			float length();

			//getters
			float xVal();
			float yVal();
			float zVal();
			float aVal();
		private:
			float x;
			float y;
			float z;
			float a;
			friend class vector3;
	};
}
#endif
