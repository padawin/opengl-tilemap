#include <iostream>
#include <iomanip>
#include "texture.hpp"
#include "font.hpp"
#include "game/config.hpp"
#include "game/utils.hpp"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <dirent.h> // for DIR
#include <algorithm> // for max
#include <ft2build.h>
#include FT_FREETYPE_H
#include "glad/glad.h"

std::string fontsDir = "/../resources/fonts/";
std::string fontSizesFile = "/../resources/fontsizes.dat";

FT_Library ft;
std::map<std::string, FT_Face> fontFaces = {};

std::map<std::string, std::map<unsigned int, FontInfo>> fontInfos = {};

bool _loadFonts();
bool _createTextureAtlases();

bool font_init() {
	if (FT_Init_FreeType(&ft)) {
		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return false;
	}
	return true;
}

bool font_loadAll() {
	return _loadFonts() && _createTextureAtlases();
}

bool _loadFonts() {
	std::string baseDir = config_getBinPath() + fontsDir;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(baseDir.c_str())) == NULL) {
		std::cerr << "Could not open resources directory: " << baseDir << std::endl;
		return false;
	}

	bool res = true;
	while ((ent = readdir(dir)) != NULL) {
		std::string fname = ent->d_name,
		            fullPath = baseDir + fname;
		if (!utils_isRegularFile(fullPath.c_str())) {
			continue;
		}

		FT_Face face;
		int error = FT_New_Face(ft, fullPath.c_str(), 0, &face);
		if (error == FT_Err_Unknown_File_Format) {
			std::cerr << "ERROR::FREETYPE: Failed to load font " << fullPath << ": Wrong format" << std::endl;
			res = false;
		}
		else if (error) {
			std::cerr << "ERROR::FREETYPE: Failed to load font " << fullPath << ": " << error << std::endl;
			res = false;
		}
		else {
			std::cout << "Font loaded: " << fullPath << std::endl;
		}
		fontFaces[fname] = face;
	}

	return res;
}
bool _createTextureAtlases() {
	fontSizesFile = config_getBinPath() + fontSizesFile;
	std::stringstream ss(utils_readFile(fontSizesFile.c_str()).c_str());
	std::string fontSize;

	bool res = true;
	while (std::getline(ss, fontSize, '\n') ) {
		if (fontSize.length() == 0) {
			continue;
		}

		const int MAX_CHARS_PER_NAME = 256;
		char fontName[MAX_CHARS_PER_NAME];
		unsigned int size = 0;
		if (sscanf(fontSize.c_str(), "%s %u", fontName, &size) != 2) {
			std::cerr << "Invalid font size definition: " << fontSize << "; expected '%s %d'\n";
			res = false;
			continue;
		}
		if (fontFaces.find(fontName) == fontFaces.end()) {
			std::cerr << "Undefined font: " << fontName << std::endl;
			res = false;
			continue;
		}
		FT_Set_Pixel_Sizes(fontFaces[fontName], 0, size);
		FT_GlyphSlot g = fontFaces[fontName]->glyph;

		if (fontInfos.find(fontName) == fontInfos.end()) {
			fontInfos[fontName] = {};
		}
		if (fontInfos[fontName].find(size) == fontInfos[fontName].end()) {
			fontInfos[fontName][size] = {};
		}

		// prepare a texture object info (w, h) for the font atlas
		// h = max(height each char)
		// w = sum(width each char)
		int atlasWidth = 0;
		int atlasHeight = 0;
		for (long unsigned int c = 32; c < 128; c++) {
			if(FT_Load_Char(fontFaces[fontName], c, FT_LOAD_RENDER)) {
				fprintf(stderr, "Loading character %c failed!\n", (char) c);
				continue;
			}

			atlasWidth += (signed) g->advance.x >> 6;
			atlasHeight = std::max(atlasHeight, (signed) g->bitmap.rows);
		}
		texture_init(fontSize, atlasWidth, atlasHeight);
		int xInAtlas = 0;
		for (long unsigned int c = 32; c < 128; c++) {
			if (FT_Load_Char(fontFaces[fontName], c, FT_LOAD_RENDER)) {
				fprintf(stderr, "Loading character %c failed!\n", (char) c);
			}

			fontInfos[fontName][size].characterInfo[c].advanceX = g->advance.x >> 6;
			fontInfos[fontName][size].characterInfo[c].advanceY = g->advance.y >> 6;

			fontInfos[fontName][size].characterInfo[c].bitmapWidth = (int) g->bitmap.width;
			fontInfos[fontName][size].characterInfo[c].bitmapHeight = (int) g->bitmap.rows;

			fontInfos[fontName][size].characterInfo[c].bitmapLeft = g->bitmap_left;
			fontInfos[fontName][size].characterInfo[c].bitmapTop = g->bitmap_top;

			fontInfos[fontName][size].characterInfo[c].textureXOffset = (float)xInAtlas / (float)atlasWidth;
			texture_addData(
				fontSize,
				g->bitmap.buffer,
				xInAtlas,
				0,
				fontInfos[fontName][size].characterInfo[c].bitmapWidth,
				fontInfos[fontName][size].characterInfo[c].bitmapHeight
			);

			xInAtlas += (int) fontInfos[fontName][size].characterInfo[c].advanceX;
		}
		std::cout << "Font atlas for font " << fontName << ", size " << size << " (texture: " << fontSize << ") loaded\n";
	}

	return res;
}

void font_clear() {
	for (auto face : fontFaces) {
		FT_Done_Face(face.second);
	}
	FT_Done_FreeType(ft);
}

FontInfo* font_getFontInfo(std::string font, unsigned int size) {
	if (fontInfos.find(font) == fontInfos.end() || fontInfos[font].find(size) == fontInfos[font].end()) {
		return NULL;
	}
	return &fontInfos[font][size];
}
