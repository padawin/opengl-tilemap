#include "opengl/texture.hpp"
#include "AnimationReader.hpp"
#include <set>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

const long unsigned MAX_CHARS_PER_LINE = 1024;
const long unsigned MAX_CHARS_PER_NAME = 128;

bool AnimationReader::process(std::string filePath, AnimationCollection *animationCollection) {
	std::ifstream fileInStream;
	fileInStream.open(filePath);

	bool valid = true;
	std::shared_ptr<Animation> currentAnimation;
	std::set<std::string> animationNames = {};
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

		if (m_currentStep == ANIMATION_START) {
			char animationName[MAX_CHARS_PER_NAME];
			int loop;
			float timePerFrame;
			if (sscanf(buf, "animationstart %s %d %f", animationName, &loop, &timePerFrame) != 3) {
				std::cerr << "Failed reading animation start line: " << buf << std::endl;
				valid = false;
				break;
			}
			else if (animationNames.find(animationName) != animationNames.end()) {
				std::cerr << "Animation " << animationName << " already exists" << std::endl;
				valid = false;
				break;
			}
			currentAnimation = animationCollection->createAnimation(animationName, (bool) loop, timePerFrame);
			m_currentStep = ANIMATION_FRAME;
		}
		else if (m_currentStep == ANIMATION_FRAME) {
			if (strncmp(buf, "animationend", 13) == 0) {
				m_currentStep = ANIMATION_START;
				continue;
			}
			char textureName[MAX_CHARS_PER_NAME];
			float w, h;
			int x, y, atlasWidth, atlasHeight;
			int res = sscanf(buf, "%s %f %f %d %d %d %d", textureName, &w, &h, &x, &y, &atlasWidth, &atlasHeight);
			if (res != 7) {
				std::cerr << "Failed reading animation frame: " << buf << std::endl;
				valid = false;
				break;
			}
			currentAnimation->addFrame(texture_get(textureName), w, h, (unsigned) x, (unsigned) y, (unsigned) atlasWidth, (unsigned) atlasHeight);
		}
	}

	fileInStream.close();
	return valid;
}
