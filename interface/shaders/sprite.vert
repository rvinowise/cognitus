#version 130
//#version 450

in vec4 vertex;
in vec2 texCoord;

uniform mat4 matrix;
uniform float is_selected;

out vec2 texc;
out float is_selected2;

void main(void)
{
    gl_Position = matrix * vertex;
    texc = texCoord;
	is_selected2 = is_selected;
}
