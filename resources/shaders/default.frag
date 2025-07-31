#version 330 core

layout (location=0) out vec4 FragColor;

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
	vec4 sample = texture(Texture, TexCoord);

	if (sample.a < 0.1) discard;
	FragColor = sample * vec4(Color, 1.0);
}