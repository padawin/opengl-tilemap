#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tileAtlas;
uniform sampler2D tilemap;
uniform uint tileAtlasWidth;
uniform uint tileAtlasHeight;

float tileWidthFraction = 1.0f / tileAtlasWidth;
float tileHeightFraction = 1.0f / tileAtlasHeight;

void main() {
	// Get the tile position (the conversion to int gives the tile coordinates)
	// No conversion is needed as the tiles have a size of 1x1
	ivec2 tilePos = ivec2(TexCoord.xy);

	// With these coordinates, get the index of the tile to use in the tilemap
	float index = texelFetch(tilemap, tilePos, 0).r;
	// From Tiled format, the index 0 means no tile, then the other indexes can
	// be -1'ed to get the actual index
	if (index == 0) {
		discard;
	}

	index--;
	// From the index, we can compute the location of the tile texture we want
	// in the texture atlas. For example with a 4 textures atlas:
	//
	//   0    0.5  1
	//     +---+---+
	//     | 0 | 1 |
	// 0.5 +---+---+
	//     | 2 | 3 |
	//   1 +---+---+
	//
	// Two textures are on the first row, and the two others on the second row.
	// - index modulo 2 returns the column (0 or 1)
	// - index divided by 2 returns the row (0 or 1)
	// Multiply by 0.5 to get the values in the range { 0 , 0.5 }
	// 2 => tileAtlasWidth
	// 0.5 => tileWidthFraction
	vec2 baseTilePos = floor(vec2(
		mod(index, tileAtlasWidth),
		index / tileAtlasWidth
	));
	baseTilePos.x *= tileWidthFraction;
	baseTilePos.y *= tileHeightFraction;

	// - Take the input texture coordinate
	// - modulo 1 to map to the { 0 , 1.0 } range
	// - Multiply by tileWidthFraction to get the values in the range
	//   {0 , tileWidthFraction}
	vec2 internalPos = mod(TexCoord.xy, 1);
	internalPos.x *= tileWidthFraction;
	internalPos.y *= tileHeightFraction;

	// Finally fetch the texel but adding the two positions
	vec2 atlasPos = baseTilePos + internalPos;
	vec4 color = texture(tileAtlas, atlasPos);
	if (color.a < 0.1) {
		discard;
	}
	else {
		FragColor = color;
	}
}
