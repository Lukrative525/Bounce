#version 330 core

layout(location = 0) in vec3 position; // Vertex position attribute
layout(location = 1) in vec3 instancePosition; // Instance position attribute

uniform mat4 projection; // Projection matrix
uniform mat4 view; // View matrix

void main()
{
    // Calculate the final vertex position
    gl_Position = projection * view * vec4(position, 1.0);
}
