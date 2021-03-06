#include "Animation.hpp"

AnimationComponent::AnimationComponent(std::shared_ptr<GameObject> owner, std::shared_ptr<ObjectRenderer> renderer) :
	RendererComponent(owner, renderer)
{
}

void AnimationComponent::addAnimation(std::string name, std::shared_ptr<Animation> animation) {
	m_mAnimations[name] = animation;
	m_sCurrentAnimation = name;
}

void AnimationComponent::start(std::string name) {
	if (m_mAnimations.find(name) == m_mAnimations.end()) {
		return;
	}
	m_sCurrentAnimation = name;
	m_mAnimations[name]->start();
}

void AnimationComponent::stop() {
	m_mAnimations[m_sCurrentAnimation]->stop();
}

void AnimationComponent::update() {
	m_mAnimations[m_sCurrentAnimation]->update();
}

void AnimationComponent::render(std::shared_ptr<Camera> camera) {
	Sprite currSprite = m_mAnimations[m_sCurrentAnimation]->getSprite();
	m_renderer->setTexture("spriteSheet", currSprite.texture);
	m_renderer->setUniform("width", currSprite.width);
	m_renderer->setUniform("height", currSprite.height);
	m_renderer->setUniform("x", currSprite.x);
	m_renderer->setUniform("y", currSprite.y);
	m_renderer->setUniform("sheetWidth", currSprite.sheetWidth);
	m_renderer->setUniform("sheetHeight", currSprite.sheetHeight);
	RendererComponent::render(camera);
}
