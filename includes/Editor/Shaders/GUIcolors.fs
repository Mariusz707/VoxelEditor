#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = vec4(1.f, 1.f, 0.f, 1.f);
}