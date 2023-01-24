#include "shader.h"
#include <matrix.h>
#include <glad/glad.h>
#include <cstdio>
#include <cerrno>

unsigned int shaderVariables::hash( std::string key) {
    unsigned int sum;

    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }

    return sum % 100;
}

/**
 * Type is specified with an enum starting wtih an enum values can be found in shader.h
*/
void shaderVariables::addVariable( variableType type, std::string name, void * value ) {
    unsigned int loc = hash(name);
    shaderVar * newVar = new shaderVar{name, value, type, NULL};
    if( variables[loc] == NULL ) {
        variables[loc] = newVar;
        return;
    }
    shaderVar * tmp = variables[loc];
    while( tmp->next != NULL ) {
        if( tmp->name == name ) {
            printf("this shader already has a value assigned to %s please check your shaders", name.c_str());
            return;
        }
        tmp = tmp->next;
    }

    tmp->next = newVar;
}

void shaderVariables::updateVariable( std::string name, void * newValue ) {
    int hashval = this->hash(name);

    shaderVariable * tmp = variables[hashval];
    if( tmp == NULL ) {
        printf("no shader variable with this name");
        return;
    }

    while( tmp->name != name ) {
        if(tmp == NULL) {
            return;
        }
        
        tmp = tmp->next;
    }

    void * returnVal = tmp->value;

    tmp->value = value;

    return returnVal;
}

void shaderVariables::applyVariables( unsigned int shaderProgram ) {
    for(int i = 0; i < 100 ; i++) {
        shaderVar * currentVar = variables[i];

        if(currentVar == NULL) {
            continue;
        }

        while( currentVar != NULL) {
            GLint loc = glGetUniformLocation( shaderProgram, currentVar->name.c_str());
            switch (currentVar->type) {
                case floatVal:
                    glUniform1f(loc, currentVar->value);
                    break;
                case vec2:
                    glUniform2f(loc, currentVar->value)
                    break;
                case vec3:
                    glUniform3f(loc, currentVar->value)
                   break;
                case vec4:
                    glUniform4f(loc, currentVar->value)
                    break;
                case mat2:
                    glUniformMatrix2fv(loc,1,GL_FALSE, currentVar->value->toArray());
                    break;
                case mat3:
                    glUniformMatrix3fv(loc,1,GL_FALSE, currentVar->value->toArray());
                    break;
                case mat4:
                    glUniformMatrix4fv(loc,1,GL_FALSE, currentVar->value->toArray());
                    break;
            }

            currentVar = currentVar->next;
        }
    }
}

shader::shader(){
    vertexShaderSource = "";
    fragmentShaderSource = "";
    shaderProgram = NULL;
}

shader::shader(std::string vertex, bool vertexFile, std::string fragment, bool fragFile) {
    this->setVertexShader(vertex,vertexFile);
    this->setFragmentShader(fragment,fragFile);
}

void shader::setVertexShader(std::string vertex, bool file) {
    FILE * fp;
    if( file ) {
        fp = fopen( vertex.c_str(), "r");
        if(fp) {
            fseek(fp, 0, SEEK_END);
            vertexShaderSource.resize(ftell(fp));
            rewind(fp);
            fread( &vertexShaderSource[0], 1, vertexShaderSource.size(), fp);
            fclose(fp);
        }
    } else {
        vertexShaderSource = vertex.c_str();
    }
}

void shader::setFragmentShader(std::string fragment, bool file) {
    FILE * fp;
    if(file) {
        fp = fopen( fragment.c_str(), "r");
        if(fp) {
            fseek(fp, 0, SEEK_END);
            fragmentShaderSource.resize(ftell(fp));
            rewind(fp);
            fread( &fragmentShaderSource[0], 1, fragmentShaderSource.size(), fp);
            fclose(fp);
        }
    } else {
        fragmentShaderSource = fragment.c_str();
    }
}

void shader::compile() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char * vertexCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexCStr, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fragmentCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentCStr, NULL);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
}

unsigned int shader::getProgram() {
    return this->shaderProgram;
}