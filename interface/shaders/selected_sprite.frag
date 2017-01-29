#version 130
//#version 450

uniform sampler2D texture;
varying vec2 texc;
varying float is_selected2;
out vec4 diffuse_color;

void main(void)
{
	vec4 texture_color = texture2D(texture, texc);
	
	if (is_selected2 > 0) 
		diffuse_color = vec4(texture_color.r+texc.x,texture_color.g+texc.y,texture_color.b,texture_color.w);
	else
		diffuse_color = texture_color;
}
