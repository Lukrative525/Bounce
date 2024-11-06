#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textureMap;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0) * texture(textureMap, TexCoord);
}
