#include "Animation.hpp"

Animation::Animation(bool loop, float timePerFrame) :
	m_bLoop(loop),
	m_fTimePerFrame(timePerFrame)
{
}

void Animation::addFrame(
	unsigned int textureID,
	float width, float height,
	unsigned int x, unsigned int y,
	unsigned int sheetWidth, unsigned int sheetHeight
) {
	Sprite frame;
	frame.texture = textureID;
	frame.width = width;
	frame.height = height;
	frame.x = x;
	frame.y = y;
	frame.sheetWidth = sheetWidth;
	frame.sheetHeight = sheetHeight;
	m_vFrames.push_back(frame);
}

Sprite &Animation::getSprite() {
	return m_vFrames[m_iCurrentFrame];
}

void Animation::start() {
	m_fTimeStart = glfwGetTime();
}

void Animation::update() {
	long unsigned nbFrames = m_vFrames.size();
	m_iCurrentFrame = (long unsigned) ((glfwGetTime() - m_fTimeStart) / m_fTimePerFrame);
	if (m_bLoop) {
		m_iCurrentFrame = m_iCurrentFrame % nbFrames;
	}
	else if (m_iCurrentFrame >= nbFrames) {
		m_iCurrentFrame = nbFrames - 1;
	}
}
