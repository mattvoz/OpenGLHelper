#ifndef __SCENE_OBJECT__
#define __SCENE_OBJECT__

#include <matrix.h>
#include <vector.h>

class graphicsObject {
    public:
        void render();
    
    private:
        GLVector::vector3 position;
        GLMatrix::matrix4 rotation;
        GLMatrix::matrix4 translation;
        GLMatrix::matrix4 scale;

};

#endif