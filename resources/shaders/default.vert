#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 vColor;
out vec2 vTexCoord;

void main()
{
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vColor = aColor;
    vTexCoord = aTexCoord;
}