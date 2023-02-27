#ifndef __SCENE_OBJECT__
#define __SCENE_OBJECT__

#include <string>
#include <vector.h>
#include <vector>
#include <matrix.h>

class graphicsInterface;

typedef struct graphicsChildContainer {
    graphicsInterface * object;
    std::string name;
} graphicsChildContainer;

class graphicsInterface {
    public:
        virtual void render( GLMatrix::matrix4 & world/*, GLMatrix::matrix4 view, GLMatrix::matrix4 perspective */ ) {};
        void addChild( graphicsChildContainer * child ) {
            children.push_back(child);
        }
    protected:
        GLVector::vector3 position;
        GLMatrix::matrix4 rotationMatrix;
        GLMatrix::matrix4 scale;
        std::vector<graphicsChildContainer *> children;
        
    private:
};

#endif