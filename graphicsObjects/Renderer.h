#ifndef __GL__RENDERER__
#define __GL__RENDERER__

#include "Scene.h";
#include "glCamera.h";

class Renderer {
    private:
    public:
        void render(Scene scene, glCamera camera);
        unsigned int renderToFrameBuffer(Scene scene, glCamera camera);
};

#endif