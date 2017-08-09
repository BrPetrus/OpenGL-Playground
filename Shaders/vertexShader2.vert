#version 410

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColour;

out vec3 colour;

uniform mat4 matrix;

void main() {
    colour = vertexColour;
    gl_Position = matrix * vec4(vertexPosition, 1.0);
}