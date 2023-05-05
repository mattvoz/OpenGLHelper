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
void shaderVariables::setVariable( variableType type, std::string name, void * value ) {
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


    while( tmp->next != NULL ) {
        if(tmp->name == newVar->name ) {
            if( tmp->type != newVar->type ) {
                printf("type mismatch for variable %s, original is %d, new is %d", name.c_str(), tmp->type, type);
                return;
            }
            tmp->value = value;
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
            printf("got var location %d for variable with name %s\n", loc, currentVar->name.c_str() );
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
    "attribute vec3 aPos;\n"
    "attribute vec3 aNormal;\n"
    "attribute vec4 aTangent;\n"
    "attribute vec2 aTexture;\n"
	"uniform mat4 model;\n"
    "uniform mat4 world;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"varying vec4 color;\n"
    "void main() {\n"
	"	color = vec4(aPos.xyz, 1.0);\n"
    "   gl_Position = projection * view * world * model * vec4(aPos, 1.0);\n"
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
    this->variables = new shaderVariables();
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
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char * vertexCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexCStr, NULL);
    glCompileShader(vertexShader);

    GLint success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if( success == -1) {
        printf("failed to compile shader");
        exit(1);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fragmentCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentCStr, NULL);
    glCompileShader(fragmentShader);
    
    success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if( success == -1) {
        printf("failed to compile shader");
        exit(1);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    

    glLinkProgram(shaderProgram);
}

unsigned int Shader::getProgram() {
    if( needsCompile ) {
        this->compile();
        needsCompile = false;
    }
    return this->shaderProgram;
}

void Shader::applyVariables() {
    this->variables->applyVariables(this->shaderProgram );
}

void Shader::setVariable(variableType type, std::string name, void * value) {
    this->variables->setVariable( type, name, value);

}

void Shader::setVariables( shaderVariables * newVars ) {
    delete this->variables;
    this->variables = newVars;
}