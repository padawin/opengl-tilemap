#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D spriteSheet;
uniform uint x;
uniform uint y;
uniform uint sheetWidth;
uniform uint sheetHeight;

void main()
{
	vec4 color = texture(
		spriteSheet,
		vec2((x + TexCoord.x) / sheetWidth, (y + TexCoord.y) / sheetHeight)
	);
	if (color.a < 0.1) {
		discard;
	}
	else {
		FragColor = color;
	}
}
