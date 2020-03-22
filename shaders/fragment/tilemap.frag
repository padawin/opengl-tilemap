#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tileAtlas;
uniform sampler2D tilemap;

void main()
{
	if (TexCoord.x >= 5) {
		FragColor = texture(tilemap, TexCoord);
	}
	else {
		FragColor = texture(tileAtlas, -TexCoord);
	}
	//FragColor = mix(texture(tilemap, TexCoord), texture(tileAtlas, -TexCoord), 0.2);
}
