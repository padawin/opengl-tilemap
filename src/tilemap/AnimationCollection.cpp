#include "AnimationCollection.hpp"

std::shared_ptr<Animation> AnimationCollection::createAnimation(std::string name, bool loop, float timePerFrame) {
	m_mAnimations[name] = std::shared_ptr<Animation>(new Animation(loop, timePerFrame));
	return m_mAnimations[name];
}
