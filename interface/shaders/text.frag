#version 130
//#version 450

in vec2 tex_coord_from_vert;

uniform sampler2D texture;
uniform vec4 color;

out vec4 diffuse_color;


void main(void)
{
	vec4 texture_color = texture2D(texture, tex_coord_from_vert);
	
	diffuse_color = texture_color + color;
}
