#include <iostream>
#include "Sprite.hpp"

SpriteComponent::SpriteComponent(
	std::shared_ptr<GameObject> owner,
	std::shared_ptr<ObjectRenderer> renderer,
	unsigned int textureID,
	float width, float height,
	unsigned int x, unsigned int y,
	unsigned int sheetWidth, unsigned int sheetHeight
) :
	RendererComponent(owner, renderer),
	m_iTexture(textureID),
	m_fWidth(width),
	m_fHeight(height),
	m_iX(x),
	m_iY(y),
	m_iSheetWidth(sheetWidth),
	m_iSheetHeight(sheetHeight)
{
}

void SpriteComponent::render(std::shared_ptr<Camera> camera) {
	m_renderer->setTexture("spriteSheet", m_iTexture);
	m_renderer->setUniform("width", m_fWidth);
	m_renderer->setUniform("height", m_fHeight);
	m_renderer->setUniform("x", m_iX);
	m_renderer->setUniform("y", m_iY);
	m_renderer->setUniform("sheetWidth", m_iSheetWidth);
	m_renderer->setUniform("sheetHeight", m_iSheetHeight);
	RendererComponent::render(camera);
}
