#ifndef __TILEMAP_READER__
#define __TILEMAP_READER__

#include <string>
#include <map>
#include <vector>

typedef enum {SIZE, LAYER_START, LAYER_ATLAS, LAYER, PROPERTY_LAYER, END_LAYER} TilemapParseStep;

typedef struct {
	std::map<const char*, unsigned int> textures = {};
	unsigned int atlasWidth = 0;
	unsigned int atlasHeight = 0;
	float zPos = 0.0f;
} TilemapLayerData;

class Tilemap;

class TilemapReader {
	private:
	TilemapParseStep m_currentStep = SIZE;

	public:
	bool process(std::string filePath, Tilemap *data);
};

#endif
