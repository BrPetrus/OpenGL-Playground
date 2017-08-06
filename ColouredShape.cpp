#include "ColouredShape.h"



ColouredShape::ColouredShape(std::string vs, std::string fs, const GLfloat* points, const int count, const GLfloat* colour, const int countColour) :
Shape(vs, fs, points, count), colour(&colour[0]), countColour(countColour)
{
    createColourVBO();
}

ColouredShape::~ColouredShape()
{
}

void ColouredShape::createColourVBO()
{
    glGenBuffers(1, &colourVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * countColour, colour, GL_STATIC_DRAW);
}

void ColouredShape::createVAO()
{
    // Create VAO object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Define memory layout of first attribute - location of vertices
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    // Define memory layout of second attrbute - colour values
    glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    // Enable vertex array at specified location
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void ColouredShape::prepare()
{
    createVAO();
    shader.createProgram();
    shader.useProgram();
    //shader.setInputColour(1.0, 1.0, 1.0, 1.0);
}

void ColouredShape::draw()
{
    shader.useProgram();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
}
