#version 130
//#version 450

in vec4 vertex;
in vec2 tex_coord;

uniform mat4 matrix;
uniform vec4 color;

out vec2 tex_coord_from_vert;
out vec4 color_from_vert;

void main(void)
{
    gl_Position = matrix * vertex;
    tex_coord_from_vert	= tex_coord;
	color_from_vert = color;
}
