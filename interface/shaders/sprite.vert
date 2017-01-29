#version 130
//#version 450

attribute vec4 vertex;
attribute vec2 texCoord;
varying vec2 texc;
uniform mat4 matrix;

uniform float is_selected;
varying float is_selected2;

void main(void)
{
    gl_Position = matrix * vertex;
    texc = texCoord;
	is_selected2 = is_selected;
}
