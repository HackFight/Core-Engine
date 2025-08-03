#version 330 core
out vec4 FragColor;
  
in vec2 vTexCoords;

uniform sampler2D screenTexture;
uniform vec2 TexCoordOffset;

void main()
{ 
    vec4 sample = texture(screenTexture, vTexCoords + TexCoordOffset);
	if (sample.a < 0.1f) discard;
	FragColor = sample;
}