#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 color;
//uniform sampler2D tileAtlas;
//uniform sampler2D tilemap;

void main()
{
	FragColor = texture(ourTexture, TexCoord) * vec4(color, 1.0);
}
