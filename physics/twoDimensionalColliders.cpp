#include <math.h>
#include <vector.h>
#include <string.h>
#include "twoDimensionalColliders.h"
#include <typeinfo>

/**
 * This class will only check for collisions in the x and y planes around a box defined by params passed in
 */
twoDimensionMeshCollider::twoDimensionMeshCollider(){
}

twoDimensionCircleCollider::twoDimensionCircleCollider(){
    center = GLVector::vector2(0, 0);
    radius = 1.0;
};

bool twoDimensionCircleCollider::checkCollisions(twoDimensionalCollider &toCheck)
{
    if (toCheck.type == CIRCLE_COLLIDER){
        twoDimensionCircleCollider & c = static_cast<twoDimensionCircleCollider&>(toCheck);
    }
    else if (type == typeid(twoDimensionBoxCollider).hash_code()){
    }
    else{
        return false;
    }
    return false;
};