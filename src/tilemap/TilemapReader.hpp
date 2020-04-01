#ifndef __TILEMAP_READER__
#define __TILEMAP_READER__

#include <string>
#include <map>
#include <vector>

typedef enum {SIZE, LAYER_START, LAYER_ATLAS, LAYER, COLLISION_LAYER, END_LAYER} ProcessStep;

typedef struct {
	std::map<const char*, unsigned int> textures = {};
	unsigned int atlasWidth = 0;
	unsigned int atlasHeight = 0;
} TilemapLayerData;

typedef struct {
	int width = 0;
	int height = 0;
	std::vector<TilemapLayerData> layers = {};
	std::vector<char> collisionMap = {};
} TilemapFileFormat;

class TilemapReader {
	private:
	ProcessStep m_currentStep = SIZE;

	public:
	bool process(std::string filePath, TilemapFileFormat &data);
};

#endif
