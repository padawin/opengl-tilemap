#ifndef __FONT__
#define __FONT__

#include <string>

typedef struct {
	long int advanceX = 0;
	long int advanceY = 0;

	int bitmapWidth = 0;
	int bitmapHeight = 0;

	int bitmapLeft = 0;
	int bitmapTop = 0;

	float textureXOffset = 0.0f;
	GLuint textureID = 0;
} CharacterInfo;

typedef struct {
	CharacterInfo characterInfo[128];
} FontInfo;

bool font_init();
bool font_loadAll();
void font_clear();
FontInfo* font_getFontInfo(std::string font, unsigned int size);

#endif
