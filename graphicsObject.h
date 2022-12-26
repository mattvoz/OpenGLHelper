#ifndef __SCENE_OBJECT__
#define __SCENE_OBJECT__

#include "./math/matrix.h"

class graphicsObject {
    public:
    
    private:
        GLMatrix::matrix4 rotation;
        GLMatrix::matrix4 translation;
        GLMatrix::matrix4 scale;

};

#endif