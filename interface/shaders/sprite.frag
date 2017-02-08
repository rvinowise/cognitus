#version 130
//#version 450

const vec4 selection_color = vec4(0,0.5,0,0);

in vec2 texc;
in float is_selected2;

uniform sampler2D texture;

out vec4 diffuse_color;

void main(void)
{
	vec4 texture_color = texture2D(texture, texc);
	
	if (is_selected2 > 0) 
		//diffuse_color = vec4(texture_color.r+texc.x,texture_color.g+texc.y,texture_color.b,texture_color.w);
		diffuse_color = texture_color + selection_color;
	else
		diffuse_color = texture_color;
}
