#include "shader.h"

#include <vector>

#include "log.h"

Shader::Shader(std::string vs, std::string fs) :
vertexShader(0), fragmentShader(0), shaderProgram(0)
{
    createShaders(vs, fs);
    createProgram();
}

Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
}

bool Shader::createShaders(std::string vs, std::string fs) {
    vertexShader = compileShader(vs.c_str(), GL_VERTEX_SHADER);
    fragmentShader = compileShader(fs.c_str(), GL_FRAGMENT_SHADER);
    
    // TODO CHANGE THIS FOR LOVE OF GOD
    return true;
}

bool Shader::createProgram() {
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
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
        log::logErrorPrint(text);
        return false;
    }
    else {
        log::logErrorPrint("Successfuly linked program.");
    }
    return true;
}

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
        log::logErrorPrint(text);
        return shader;
    }
    
    std::string text = "Unsuccessfuly compiled shader.\nShader text\"" + (std::string)shaderText + "\"\n";
    log::logErrorPrint(text);
    
    // Unsuccessful
    GLint logSize = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    GLchar log[logSize]; // Create log variable
    glGetShaderInfoLog(shader, logSize, nullptr, &log[0]);
    
    // Print log
    log::logErrorPrint(log);
    
    return 0;
} 