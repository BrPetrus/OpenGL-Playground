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
    
    virtual void draw();
    virtual void prepare();
    
    //void prepare(const GLfloat* points);
    
    const Shader& getShader() const {return shader;}
    void useProgram();
    
protected:
    GLuint pointsVBO;
    GLuint vao;
    Shader shader;
    
    // const?
    const GLfloat* points;
    const int count;
    
    void createPointsVBO();
    virtual void createVAO();
};

#endif // SHAPE_H
