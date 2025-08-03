#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

out vec2 vTexCoord;

void main()
{
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vTexCoord = aTexCoord;
}