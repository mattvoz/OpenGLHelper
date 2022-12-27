#include "shader.h"
#include <glad/glad.h>
#include <cstdio>
#include <cerrno>

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