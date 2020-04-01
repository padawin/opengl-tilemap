#ifndef __ANIMATION_COLLECTION__
#define __ANIMATION_COLLECTION__

#include "Animation.hpp"
#include <memory>
#include <string>
#include <map>

class AnimationCollection {
	private:
	std::map<std::string, std::shared_ptr<Animation>> m_mAnimations = {};

	public:
	std::shared_ptr<Animation> createAnimation(std::string name, bool loop, float timePerFrame);
	std::shared_ptr<Animation> getAnimation(std::string name);
};

#endif
