#ifndef __2D__COLLIDER__
#define __2D__COLLIDER__

#include <math.h>
#include <vector.h>
#include <typeinfo>

#define CIRCLE_COLLIDER 0
#define BOX_COLLIDER 1
#define POLY_COLLIDER 2

class twoDimensionalCollider{
    public:
        virtual bool checkCollisions(twoDimensionalCollider& arr);
        const short type;
    private:
        GLVector::vector2 direction;
        float elasticity;
};


class twoDimensionBoxCollider;
class twoDimensionCircleCollider;
class twoDimensionMeshCollider;

/**
 * This class will only check for collisions in the x and y planes around a box defined by params passed in
*/
class twoDimensionBoxCollider : private twoDimensionalCollider{
    public:
        twoDimensionBoxCollider();
        virtual bool checkCollisions( twoDimensionalCollider &);
        const short type = BOX_COLLIDER;
    private:
        float center;
        float width;
        float height;
};

class twoDimensionCircleCollider : private twoDimensionalCollider{
    public:
    twoDimensionCircleCollider();
    virtual bool checkCollisions( twoDimensionalCollider &);
    private:
        GLVector::vector2 center;
        double radius;

};

class twoDimensionMeshCollider: private twoDimensionalCollider{
    public:
    twoDimensionMeshCollider();
    virtual bool checkCollisions();
    private:
        Mesh2D mesh;

};

#endif