#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include <GL/GLFW/glfw3.h>


class Shader
{
public:
    Shader(std::string vs, std::string fs);
    ~Shader();
    
    bool createShaders(std::string vs, std::string fs);
    bool createProgram();
    void useProgram();
    void unuseProgram();
    
private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    
    GLuint compileShader(const char*, const GLenum);
};

#endif // SHADER_H
