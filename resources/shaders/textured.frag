#version 330 core

layout (location=0) out vec4 FragColor;

in vec2 vTexCoord;

uniform vec2 TexCoordOffset;

uniform sampler2D Texture;

void main()
{
	vec4 sample = texture(Texture, vTexCoord + TexCoordOffset);
	if (sample.a < 0.1f) discard;
	FragColor = sample;
}