#ifndef __GL_SHADER__
#define __GL_SHADER__

#include <iostream>
#include <string>

enum variableType { floatVal, vec2, vec3, vec4, mat2, mat3, mat4 };

typedef struct shaderVar {
    std::string name;
    void * value;
    variableType type;
    struct shaderVar * next;

} shaderVar;

class shaderVariables {
    public:
        shaderVariables(){
            for(int i = 0; i < 100; i++) {
                variables[i] = void;
            }
        };
        void addVariable( variableType type, std::string name, void * value);
        void applyVariables(unsigned int shaderProgram);
        void setVariable( std::string name, void * value);

    private:
        unsigned int hash( std::string key );
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