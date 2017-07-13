#include "shape.h"
#include <iostream>

/**
* @brief Constructs shape object.
* @param vs String, in which the vertex shader code is stored.
* @param fs String, in which the fragment shader code is stored.
* @param points Vertex data.
* @param count How many vertices are in the array.
*/
Shape::Shape(std::string vs, std::string fs, const GLfloat* points, const int count) :
 vbo(0), vao(0), shader(vs, fs), points(&points[0]), count(count)
{
    createVBO();
    createVAO();
}

Shape::~Shape()
{
}

/**
* @brief Activate shader program, binds VAO and draws shape obj on screen.
*/
void Shape::draw() {
    shader.useProgram();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
}
    

/**
* @brief Creates VBO and put data inside.
*/
void Shape::createVBO() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Check if buffer works
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), points, GL_STATIC_DRAW);
}

/**
* @brief Creates VAO object and describe memory layout.
*/
void Shape::createVAO() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Not really necessary here
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Define memory layout TODO: make it more modular
}
