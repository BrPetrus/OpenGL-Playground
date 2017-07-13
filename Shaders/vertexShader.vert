#version 410
in vec3 pos;

void main() {
    gl_Position = vec4(pos.x - 0.25, pos.y + 0.0, pos.z, 1.0);
}