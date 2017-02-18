#version 130
//#version 410

in vec4 color_from_vert;
out vec4 diffuse_color;

void main(void)
{
    diffuse_color = color_from_vert;
	//return vec4(1,1,1,0.5);
}
