#ifndef COLOUREDSHAPE_H
#define COLOUREDSHAPE_H

#include "shape.h" // Base class: Shape

class ColouredShape : public Shape
{
public:
    ColouredShape(std::string vs, std::string fs, const GLfloat* points, const int count, const GLfloat* colour, const int countColour);
    ~ColouredShape();
    
    virtual void draw();
    virtual void prepare();
    
private:
    GLuint colourVBO;
    
    const GLfloat* colour;
    const int countColour;
    
    void createColourVBO();
    virtual void createVAO();

};

#endif // COLOUREDSHAPE_H
