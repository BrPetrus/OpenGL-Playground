#include "shader.h"

#include <vector>
//#include <iostream>

#include "log.h"

/**
*   Creates objects and prepares it for drawing.
*   @param vs Code for vertex shader.
*   @param fs Code for fragment shader.
*/
Shader::Shader() :
shaderProgram(0)
{}

Shader::~Shader()
{
    //TODO iterate through vector and delete shaders
    for(std::vector<GLenum>::iterator it = shaders.begin(); it != shaders.end(); it++) {
       glDeleteShader(*it);
    }
    glDeleteProgram(shaderProgram);
}

/*bool Shader::createShaders(std::string vs, std::string fs) {
    vertexShader = compileShader(vs.c_str(), GL_VERTEX_SHADER);
    fragmentShader = compileShader(fs.c_str(), GL_FRAGMENT_SHADER);
    
    // TODO CHANGE THIS FOR LOVE OF GOD
    return true;
}*/

void Shader::addShader(std::string source, GLenum type) {
    GLuint shader = compileShader(source.c_str(), type);
    shaders.push_back(shader);
}

bool Shader::createProgram() {
    shaderProgram = glCreateProgram();
    //Iterate through shaders vector and attach them
    for(std::vector<GLenum>::iterator it = shaders.begin(); it != shaders.end(); it++) {
        glAttachShader(shaderProgram, *it);
    }
    glLinkProgram(shaderProgram);
    
    // Check if it's linked
    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&isLinked);
    if(isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
        std::string text = "Error while linking the program: ";
        for(auto i = infoLog.begin(); i != infoLog.end(); i++) {
            text += *i;
        }
        logTools::logErrorPrint(text);
        return false;
    }
    else {
        //std::cout << "\t\tLinking done; searching for uniform";
        std::string tmp = "Uniform: 5";
        logTools::logErrorPrint(tmp);
        logTools::logErrorPrint("Successfuly linked program.");
    }
    
    
    return true;
}

/**
*   Loads shader program into memory
*/
void Shader::useProgram() {
    glUseProgram(shaderProgram);
}
void Shader::unuseProgram() {
    glUseProgram(0);
}

GLuint Shader::compileShader(const char* shaderText, const GLenum shaderType) {
    // Create shader object
    GLuint shader = glCreateShader(shaderType);
    
    // Put the shader inside shader object
    glShaderSource(shader, 1, &shaderText, nullptr);
    
    // Compile the shader
    glCompileShader(shader);
    
    // Error handling
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    // Successful
    if (success == GL_TRUE) {
        std::string text = "Successfuly compiled shader.\nShader text\"" + (std::string)shaderText + "\"\n";
        logTools::logErrorPrint(text);
        return shader;
    }
    
    std::string text = "Unsuccessfuly compiled shader.\nShader text\"" + (std::string)shaderText + "\"\n";
    logTools::logErrorPrint(text);
    
    // Unsuccessful
    GLint logSize = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    GLchar logTools[logSize]; // Create log variable
    glGetShaderInfoLog(shader, logSize, nullptr, &logTools[0]);
    
    // Print log
    logTools::logErrorPrint(logTools);
    
    return 0;
} 