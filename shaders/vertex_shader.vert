#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 instancePosition;
layout(location = 2) in float instanceScale;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(instanceScale * position + instancePosition, 1.0);
}
