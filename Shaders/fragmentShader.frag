#version 410
out vec4 frag_colour;

uniform vec4 inputColour;

void main() {
    frag_colour = vec4(inputColour.rgba);
}