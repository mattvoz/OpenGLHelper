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
                variables[i] = NULL;
            }
        };
        void addVariable( variableType type, std::string name, void * value);
        /**
         * This function will return the void * of the previous data so if it's allocated it can be deleted.
        */
        void * updateVariable( std::string name, void * newValue );
        void applyVariables(unsigned int shaderProgram);
        void setVariable( std::string name, void * value);

    private:
        unsigned int hash( std::string key );
        struct shaderVar * variables[100];

};

class Shader{
    public:
        Shader( std::string, bool, std::string, bool);
        Shader();
        void setVertexShader(std::string, bool);
        void setFragmentShader(std::string, bool);
        void setVariables( shaderVariables * newVars );
        void applyVariables();
        void setVariable(variableType type, std::string name, void * value);
        void compile();
        unsigned int getProgram();
    private:
        std::string vertexShaderSource;
        std::string fragmentShaderSource;
        unsigned int shaderProgram;
        shaderVariables * variables = new shaderVariables();
        bool needsCompile;
        unsigned int fragmentShader;
        unsigned int vertexShader;

};

#endif