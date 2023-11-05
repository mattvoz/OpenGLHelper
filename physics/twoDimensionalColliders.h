#ifndef __2D__COLLIDER__
#define __2D__COLLIDER__

#include <math.h>
#include <vector.h>

/**
 * This class will only check for collisions in the x and y planes around a box defined by params passed in
*/
class twoDimensionBoxCollider{
    GLVector::vector2 points[4];
};

class twoDimensionCircileCollider{
    GLVector::vector2 center;
    double radius;

};

class twoDimensionMeshCollider{
};

#endif