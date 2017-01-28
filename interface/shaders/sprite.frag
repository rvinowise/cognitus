uniform sampler2D texture;
varying vec2 texc;
out vec4 diffuseColor;

void main(void)
{
    diffuseColor = texture2D(texture, texc);
}
