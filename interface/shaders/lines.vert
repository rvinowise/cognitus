#version 130
//#version 410

in vec4 vertex;
in vec4 color;
uniform mat4 matrix;

out vec4 color_from_vert;



void main(void)
{
    gl_Position = matrix * vertex;
	color_from_vert = color;
}

