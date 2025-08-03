#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 vTexCoords;

uniform float HorizontalOffset;

void main()
{
    gl_Position = vec4(aPos.x + HorizontalOffset, aPos.y, 0.0, 1.0); 
    vTexCoords = aTexCoords;
}  