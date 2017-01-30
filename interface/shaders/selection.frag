#version 130
//#version 450

out vec4 diffuseColor;
uniform vec4 color;

void main(void)
{
    diffuseColor = color;
	//return vec4(1,1,1,0.5);
}
