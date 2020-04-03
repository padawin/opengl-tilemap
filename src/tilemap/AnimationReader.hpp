#ifndef __ANIMATION_READER__
#define __ANIMATION_READER__

#include <string>
#include "AnimationCollection.hpp"

typedef enum {ANIMATION_START, ANIMATION_FRAME} AnimationParseStep;

class AnimationReader {
	private:
	AnimationParseStep m_currentStep = ANIMATION_START;

	public:
	bool process(std::string filePath, AnimationCollection *animationCollection);
};

#endif
