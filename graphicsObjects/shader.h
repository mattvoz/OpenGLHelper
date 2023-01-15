#ifndef __GL_SHADER__
#define __GL_SHADER__

#include <iostream>
#include <string>

enum variableType { floatVal, vec2, vec3, vec4, mat2, mat3, mat4 };

typedef struct shaderVar {
    std::string name;
    void * value;
    struct shaderVar * next;

} shaderVar;

class shaderVariables {
    public:
        void addVariable( variableType type, shaderVar * value);
        void applyVariables(unsigned int shaderProgram);
        void setVariable( std::string name, void * value);

    private:
        int hash();
        shaderVar variables[100];

};

class shader{
    public:
        shader( std::string, bool, std::string, bool);
        shader();
        void setVertexShader(std::string, bool);
        void setFragmentShader(std::string, bool);
        void compile();
        unsigned int getProgram();
    private:
        std::string vertexShaderSource;
        std::string fragmentShaderSource;
        unsigned int shaderProgram;
        shaderVariables variables;

};

#endif