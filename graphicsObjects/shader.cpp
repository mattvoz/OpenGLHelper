#include "shader.h"
#include <cstdio>
#include <cerrno>

shader::shader(){
    vertexShader = NULL;
    fragmentShader = NULL;
    shaderProgram = NULL;
}

shader::shader(std::string vertex, bool vertexFile, std::string fragment, bool fragFile) {
    FILE * fp;
    if( vertexFile ) {
        fp = fopen( vertex.c_str(), "r");
        if(fp) {
            fseek(fp, 0, SEEK_END);
            vertexShader.resize(ftell(fp));
            rewind(fp);
            fread( &vertexShader[0], 1, vertexShader.size(), fp);
            fclose(fp);
        }
    } else {
        vertexShader = vertex.c_str();
    }

    if(fragFile) {
        fp = fopen( fragment.c_str(), "r");
        if(fp) {
            fseek(fp, 0, SEEK_END);
            fragmentShader.resize(ftell(fp));
            rewind(fp);
            fread( &fragmentShader[0], 1, vertexShader.size(), fp);
            fclose(fp);
        }
    } else {
        fragmentShader = fragment.c_str();
    }
}