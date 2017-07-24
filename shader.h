#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/GLFW/glfw3.h>


class Shader
{
public:
    Shader();
    ~Shader();
    
    //bool createShaders(std::string vs, std::string fs);
    void addShader(std::string, GLenum);
    
    bool createProgram();
    void useProgram();
    void unuseProgram();
    void setInputColour(float r, float g, float b, float a);
    
    
    const GLuint& getShaderProgram() const {return shaderProgram;}
private:
    std::vector<GLuint> shaders;
    GLuint shaderProgram;
    
    GLuint compileShader(const char*, const GLenum);
    GLuint inputColour;
};

#endif // SHADER_H
