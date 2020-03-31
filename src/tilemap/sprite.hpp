#ifndef __SPRITE__
#define __SPRITE__

typedef struct {
	unsigned int texture;
	float width;
	float height;
	unsigned int x;
	unsigned int y;
	unsigned int sheetWidth;
	unsigned int sheetHeight;

} Sprite;

#endif
