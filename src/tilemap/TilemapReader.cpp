#include "TilemapReader.hpp"
#include "opengl/texture.hpp"
#include <set>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

const long unsigned MAX_CHARS_PER_LINE = 1024;
const long unsigned MAX_CHARS_PER_NAME = 128;

bool TilemapReader::process(std::string filePath, TilemapFileFormat &data) {
	std::ifstream fileInStream;
	fileInStream.open(filePath);

	bool valid = true;
	char layerName[MAX_CHARS_PER_NAME];
	float* content = 0;
	bool contentOpen = false;
	unsigned long contentSize = 0;
	unsigned long contentFilled = 0;
	TilemapLayerData layerData;
	std::set<std::string> layerNames = {};
	while (!fileInStream.eof()) {
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
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
			if (sscanf(buf, "size %d %d", &data.width, &data.height) != 2) {
				std::cerr << "Failed reading size: " << buf << std::endl;
				valid = false;
				break;
			}
			contentSize = (unsigned) (data.width * data.height);
			m_currentStep = LAYER_START;
		}
		else if (m_currentStep == LAYER_START) {
			int res = sscanf(buf, "layerstart %s", layerName);
			if (res != 1) {
				std::cerr << "Layer start missing" << std::endl;
				valid = false;
				break;
			}
			else if (layerNames.find(layerName) != layerNames.end()) {
				std::cerr << "Layer " << layerName << " already exists" << std::endl;
				valid = false;
				break;
			}
			m_currentStep = LAYER_ATLAS;
			content = (float*) malloc(contentSize * sizeof(float));
			contentFilled = 0;
			contentOpen = true;
			layerData = TilemapLayerData();
			continue;
		}
		else if (m_currentStep == LAYER_ATLAS) {
			unsigned int atlasWidth, atlasHeight;
			char atlasName[MAX_CHARS_PER_NAME];
			if (sscanf(buf, "atlas %s %u %u", atlasName, &atlasWidth, &atlasHeight) != 3) {
				std::cerr << "Failed reading atlas: " << buf << std::endl;
				valid = false;
				break;
			}

			layerData.textures["tileAtlas"] = texture_get(atlasName);
			layerData.atlasWidth = atlasWidth;
			layerData.atlasHeight = atlasHeight;
			m_currentStep = LAYER;
		}
		else if (m_currentStep == LAYER) {
			if (strncmp(buf, "layerend", 9) == 0) {
				if (contentSize != contentFilled) {
					std::cerr << "Integrity check failed: layer " << layerName
							  << " content has an invalid size (got: " << contentFilled
							  << ", expected: " << contentSize << ")" << std::endl;
					valid = false;
					break;
				}
				layerData.textures["tilemap"] = texture_loadData(
					layerName, data.width, data.height, content
				);
				free(content);
				contentOpen = false;
				data.layers.push_back(layerData);
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
				content[contentFilled] = (float) val;
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
