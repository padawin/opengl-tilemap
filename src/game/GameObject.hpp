#ifndef __OBJECT__
#define __OBJECT__

#include <memory>
#include "GameObjectRenderer.hpp"
#include "Camera.hpp"

class GameObject {
	protected:
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_angle = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	public:
	virtual ~GameObject() {}
	virtual void init() {};
	virtual void setPosition(float x, float y, float z);
	virtual glm::vec3 getPosition() const;
	virtual void update();
	virtual void render(std::shared_ptr<Camera> camera, GameObjectRenderer *renderer);
	virtual void render(std::shared_ptr<Camera> camera, GameObjectRenderer *renderer, glm::vec3 position, glm::vec3 angle, glm::vec3 scale);
};

#endif
