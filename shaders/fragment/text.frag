#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D atlas;
uniform vec3 color;

void main()
{
	vec4 sampled = vec4(color, texture(atlas, TexCoord).r);
	if (sampled.a < 0.1) {
		discard;
	}
	else {
		FragColor = sampled;
	}
}
