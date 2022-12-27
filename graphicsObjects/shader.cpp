#include "shader.h"
#include <iostream.h>
#include <stdio.h>

shader::shader(){
    vertexShader = NULL;
    fragmentShader = NULL;
    shaderProgram = NULL;
}

shader(std::string vertex, bool vertexFile, std::string fragment, bool fragFile) {
    if( vertexFile ) {
        std::FILE * fp = std::fopen( vertex, "r");
        if(fp) {
            fseek
        }
    }
}