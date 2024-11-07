#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordinates;
layout(location = 2) in vec3 instancePosition;
layout(location = 3) in float instanceScale;
layout(location = 4) in vec4 instanceColor;

out vec2 TexCoord;
out vec4 Color;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(instanceScale * position + instancePosition, 1.0);
    TexCoord = textureCoordinates;
    Color = instanceColor;
}
