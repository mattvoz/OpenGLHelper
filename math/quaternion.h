#ifndef __GL_QUATERNION__
#define __GL_QUATERNION__

#include "vector.h"

class Quaternion{
    public:
    Quaternion();
    Quaternion( float x, float y, float z, float w);
    Quaternion operator+( Quaternion & operand);
    Quaternion operator-( Quaternion & operand);
    Quaternion operator*( Quaternion & operand);
    void normalize();
    private:
    GLVector::vector3 representation;
    float scalar;
};
#endif