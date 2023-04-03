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

    shaderVar * newVar = new shaderVar();
    newVar->name = name.c_str();
    newVar->type = type;
    newVar->value = value;
    newVar->next = NULL;

    if( variables[loc] == NULL ) {
        variables[loc] = newVar;
        return;
    }

    shaderVar * tmp = variables[loc];

    if( tmp->name == name ) {
        printf("this shader already has a value assigned to %s please check your shaders\n", name.c_str());
        return;
    }

    while( tmp->next != NULL ) {
        if( tmp->name == name ) {
            printf("this shader already has a value assigned to %s please check your shaders\n", name.c_str());
            return;
        }
        tmp = tmp->next;
    }

    tmp->next = newVar;
}

void * shaderVariables::updateVariable( std::string name, void * newValue ) {
    int hashval = this->hash(name);

    shaderVar * tmp = variables[hashval];
    if( tmp == NULL ) {
        printf("no shader variable with this name\n");
        return NULL;
    }

    while( tmp->name != name ) {
        if(tmp == NULL) {
            return NULL;
        }
        
        tmp = tmp->next;
    }

    void * returnVal = tmp->value;

    tmp->value = newValue;

    return returnVal;
}

void shaderVariables::applyVariables( unsigned int shaderProgram ) {
    for(int i = 0; i < 100 ; i++) {
        shaderVar * currentVar = variables[i];

        if(currentVar == NULL) {
            continue;
        }

        while( currentVar != NULL) {
            GLint loc = glGetUniformLocation( shaderProgram, currentVar->name.c_str() );
            switch (currentVar->type) {
                case floatVal:
                    glUniform1f(loc,* ( (GLfloat *) currentVar->value) );
                    break;
                case vec2:
                    glUniform2fv(loc, 2, (GLfloat *) currentVar->value);
                    break;
                case vec3:
                    glUniform3fv(loc, 3, (GLfloat *) currentVar->value);
                   break;
                case vec4:
                    glUniform4fv(loc, 4, (GLfloat *) currentVar->value);
                    break;
                case mat2:
                    glUniformMatrix2fv(loc,1,GL_FALSE, ( (GLMatrix::matrix2 *) currentVar->value )->toArray());
                    break;
                case mat3:
                    glUniformMatrix3fv(loc,1,GL_FALSE, ( (GLMatrix::matrix3 *) currentVar->value)->toArray());
                    break;
                case mat4:
                    float * tmp = ( (GLMatrix::matrix4 *) currentVar->value)->toArray();
                    glUniformMatrix4fv( loc, 1, GL_FALSE, tmp );
                    break;
            }

            currentVar = currentVar->next;
        }
    }
}

Shader::Shader(){
    vertexShaderSource = "#version 330 core\n"
    "attribute vec3 pos;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"varying vec4 color;\n"
    "void main() {\n"
	"	color = vec4(pos.xyz, 1.0);\n"
    "   gl_Position = projection * view * model * vec4(pos, 1.0);\n"
    "}\0";

    fragmentShaderSource = " #version 330 core\n"
	"out vec4 FragColor;\n"
	"varying vec4 color;"
	"void main()\n"
	"{\n"
    	"FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"FragColor.a = 1.0;\n"
	"}\0";
    this->compile();
}

Shader::Shader(std::string vertex, bool vertexFile, std::string fragment, bool fragFile) {
    this->setVertexShader(vertex,vertexFile);
    this->setFragmentShader(fragment,fragFile);
    this->compile();
}

void Shader::setVertexShader(std::string vertex, bool file) {
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

void Shader::setFragmentShader(std::string fragment, bool file) {
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

void Shader::compile() {
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

unsigned int Shader::getProgram() {
    if( needsCompile ) {
        this->compile();
    }
    return this->shaderProgram;
}

void Shader::applyVariables() {
    this->variables.applyVariables(this->shaderProgram);
}

void Shader::setVariable() {

}