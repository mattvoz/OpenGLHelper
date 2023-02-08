#ifndef __SCENE_OBJECT__
#define __SCENE_OBJECT__

#include <string>
#include <vector.h>
#include <vector>
#include <matrix.h>

typedef struct graphicsChildContainer {
    graphicsObject * object;
    std::string name;
} graphicsChildContainer;

class graphicsObject {
    public:
        virtual void render() {};
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