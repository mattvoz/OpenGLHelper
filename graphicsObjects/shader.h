#ifndef __GL_SHADER__
#define __GL_SHADER__

#include <iostream>

class shader{
    public:
        shader( std::string, bool, std::string, bool);
        shader();
        void setVertexShader(std::string, bool);
        void setFragmentShader(std::string, bool);
        void compile();
        unsigned int getProgram();
    private:
        std::string vertexShader;
        std::string fragmentShader;
        unsigned int shaderProgram;

};

#endif