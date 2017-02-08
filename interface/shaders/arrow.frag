#version 130
//#version 450


uniform vec4 color;

out vec4 diffuse_color;

void main(void)
{	
	diffuse_color = color;
}
