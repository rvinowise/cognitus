#version 130
//#version 450

out vec4 diffuse_color;
uniform vec4 color;

void main(void)
{
    diffuse_color = color;
	//return vec4(1,1,1,0.5);
}
