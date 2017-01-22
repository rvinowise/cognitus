attribute vec4 vertex;
attribute vec2 texCoord;
varying vec2 texc;
uniform mat4 matrix;

void main(void)
{
    gl_Position = matrix * vertex;
    texc = texCoord;
}
