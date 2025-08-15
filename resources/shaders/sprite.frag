#version 330 core

layout (location=0) out vec4 FragColor;

in vec2 vTexCoord;

uniform vec2 UVscale;
uniform vec2 UVtranslate;

uniform sampler2D Texture;

void main()
{
	vec4 sample = texture(Texture, vec2(vTexCoord.x * UVscale.x, vTexCoord.y * UVscale.y) + UVtranslate);
	if (sample.a < 0.1f) discard;
	FragColor = sample;
}