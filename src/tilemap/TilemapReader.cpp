#include "TilemapReader.hpp"
#include "Tilemap.hpp"
#include "opengl/texture.hpp"
#include <set>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

const long unsigned MAX_CHARS_PER_LINE = 1024;
const long unsigned MAX_CHARS_PER_NAME = 128;

const int LAYER_TYPE_TILEMAP = 0;
const int LAYER_TYPE_COLLISION = 1;

bool TilemapReader::process(std::string filePath, Tilemap *tilemap) {
	std::ifstream fileInStream;
	fileInStream.open(filePath);

	bool valid = true;
	bool contentOpen = false;
	char layerName[MAX_CHARS_PER_NAME];
	float* content = 0;
	unsigned long contentSize = 0;
	unsigned long contentFilled = 0;
	TilemapLayerData layerData;
	std::set<std::string> layerNames = {};
	while (!fileInStream.eof()) {
		char buf[MAX_CHARS_PER_LINE];
		fileInStream.getline(buf, MAX_CHARS_PER_LINE);
		if (fileInStream.fail() && !fileInStream.eof()) { // for too long lines
			std::cerr << "Failed reading line: " << buf << std::endl;
			valid = false;
			break;
		}

		if (*buf == '\0' || *buf == '#') {
			continue;
		}

		if (m_currentStep == SIZE) {
			if (sscanf(buf, "size %d %d", &tilemap->m_iWidth, &tilemap->m_iHeight) != 2) {
				std::cerr << "Failed reading size: " << buf << std::endl;
				valid = false;
				break;
			}
			contentSize = (unsigned) (tilemap->m_iWidth * tilemap->m_iHeight);
			m_currentStep = LAYER_START;
		}
		else if (m_currentStep == LAYER_START) {
			float layerZPos;
			int resLayer = sscanf(buf, "layerstart %s %f", layerName, &layerZPos);
			int resLayerProperty = sscanf(buf, "layerpropertystart %s", layerName);
			if (resLayer == 2) {
				if (layerNames.find(layerName) != layerNames.end()) {
					std::cerr << "Layer " << layerName << " already exists" << std::endl;
					valid = false;
					break;
				}
				layerData = TilemapLayerData();
				layerData.zPos = layerZPos;
				content = (float*) malloc(contentSize * sizeof(float));
				contentOpen = true;
				m_currentStep = LAYER_ATLAS;
			}
			else if (resLayerProperty == 1) {
				if (tilemap->m_mTileProperties.find(layerName) != tilemap->m_mTileProperties.end()) {
					std::cerr << "Layer property" << layerName << " already exists" << std::endl;
					valid = false;
					break;
				}
				tilemap->m_mTileProperties[layerName] = {};
				m_currentStep = PROPERTY_LAYER;
			}
			else {
				std::cerr << "Layer start missing" << std::endl;
				valid = false;
				break;
			}

			contentFilled = 0;
		}
		else if (m_currentStep == LAYER_ATLAS) {
			unsigned int atlasWidth, atlasHeight;
			char atlasName[MAX_CHARS_PER_NAME];
			if (sscanf(buf, "atlas %s %u %u", atlasName, &atlasWidth, &atlasHeight) != 3) {
				std::cerr << "Failed reading atlas: " << buf << std::endl;
				valid = false;
				break;
			}

			layerData.textures["tileAtlas"] = texture_getID(atlasName);
			layerData.atlasWidth = atlasWidth;
			layerData.atlasHeight = atlasHeight;
			m_currentStep = LAYER;
		}
		else if (m_currentStep == LAYER || m_currentStep == PROPERTY_LAYER) {
			if (strncmp(buf, "layerend", 9) == 0 || strncmp(buf, "layerpropertyend", 9) == 0) {
				if (contentSize != contentFilled) {
					std::cerr << "Integrity check failed: layer " << layerName
							  << " content has an invalid size (got: " << contentFilled
							  << ", expected: " << contentSize << ")" << std::endl;
					valid = false;
					break;
				}
				if (m_currentStep == LAYER) {
					layerData.textures["tilemap"] = texture_loadData(
						layerName, tilemap->m_iWidth, tilemap->m_iHeight, content
					);
					free(content);
					contentOpen = false;
					tilemap->m_vLayers.push_back(layerData);
				}
				m_currentStep = LAYER_START;
				continue;
			}
			else if (contentFilled == contentSize) {
				std::cerr << "Max content of " << contentSize << " items reached for layer " << layerName << std::endl;
				valid = false;
				break;
			}

			std::stringstream ss(buf);
			std::vector<float> result;
			while (ss.good()) {
				std::string substr;
				getline(ss, substr, ',');
				if (substr == "") {
					continue;
				}
				int val;
				if (sscanf(substr.c_str(), "%d", &val) != 1) {
					std::cerr << "Failed reading layer content: " << substr << " must be an integer" << std::endl;
					valid = false;
					break;
				}
				if (m_currentStep == LAYER) {
					content[contentFilled] = (float) val;
				}
				else if (m_currentStep == PROPERTY_LAYER) {
					tilemap->m_mTileProperties[layerName].push_back((char) val);
				}
				contentFilled++;
			}
		}
	}

	fileInStream.close();
	if (contentOpen) {
		free(content);
	}
	return valid;
}
