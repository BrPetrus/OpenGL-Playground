#include "shape.h"

Shape::Shape(std::string vs, std::string fs, const GLfloat* points, const int count) :
 vbo(0), vao(0), shader(vs, fs), points(&points[0]), count(count)
{
}

Shape::~Shape()
{
}

void Shape::draw() {
    shader.useProgram();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, count);
}
    

void Shape::createVBO() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Check if buffer works
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), points, GL_STATIC_DRAW);
}
void Shape::createVAO() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Not really necessary here
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Define memory layout TODO: make it more modular
}