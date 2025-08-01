#version 330 core

layout (location=0) out vec4 FragColor;

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D Texture;

void main()
{
	vec4 sample = texture(Texture, vTexCoord);

	if (sample.a < 0.1) discard;
	FragColor = sample * vec4(vColor, 1.0);
}