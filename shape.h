#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>

#include <string>

#include "shader.h"

class Shape
{
public:
    Shape(std::string vs, std::string fs, const GLfloat* points, const int count);
    ~Shape();
    
    void draw();
    
    //void prepare(const GLfloat* points);
    
private:
    GLuint vbo;
    GLuint vao;
    Shader shader;
    
    // const?
    const GLfloat* points;
    const int count;
    
    void createVBO();
    void createVAO();
};

#endif // SHAPE_H
