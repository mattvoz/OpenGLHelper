#ifndef __SCENE_OBJECT__
#define __SCENE_OBJECT__

#include <matrix.h>
#include <vector.h>

class graphicsObject {
    public:
        virtual void render() {};
    protected:
        GLVector::vector3 position;
        GLMatrix::matrix4 rotationMatrix;
        GLMatrix::matrix4 scale;
        
    private:
};

#endif