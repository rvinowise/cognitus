#version 130
//#version 450

attribute vec4 vertex;
uniform mat4 matrix;


void main(void)
{
    gl_Position = matrix * vertex;
}
