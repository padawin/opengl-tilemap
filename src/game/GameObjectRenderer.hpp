#ifndef __GAME_OBJECT_RENDERER__
#define __GAME_OBJECT_RENDERER__

#include <memory>
#include "Camera.hpp"

class GameObjectRenderer {
	public:
	virtual ~GameObjectRenderer() {}
	virtual void render(std::shared_ptr<Camera> camera) = 0;

	virtual void setScale(float x, float y, float z) = 0;
	virtual void setRotation(float x, float y, float z) = 0;
	virtual void setPosition(float x, float y, float z) = 0;
};

#endif
