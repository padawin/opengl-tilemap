#ifndef __ANIMATION__
#define __ANIMATION__

#include <vector>
#include <GLFW/glfw3.h>
#include "tilemap/sprite.hpp"

class Animation {
	private:
	bool m_bLoop;
	float m_fTimePerFrame;
	double m_fTimeStart = 0.0f;
	long unsigned m_iCurrentFrame = 0;

	std::vector<Sprite> m_vFrames = {};

	public:
	Animation(bool loop, float timePerFrame);
	void addFrame(
		unsigned int textureID,
		float width, float height,
		unsigned int x, unsigned int y,
		unsigned int sheetWidth, unsigned int sheetHeight
	);
	Sprite &getSprite();
	void start();
	void update();
};

#endif
