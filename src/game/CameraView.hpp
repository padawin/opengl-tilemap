#ifndef __CAMERA_VIEW__
#define __CAMERA_VIEW__

#include <glm/glm.hpp>

class CameraView {
	protected:
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 m_view = glm::mat4(0.0f);

	public:
	virtual ~CameraView() {}
	virtual void setPosition(glm::vec3 position);

	virtual glm::vec3 getPosition() const;
	virtual glm::mat4 get() const;

	virtual void update() = 0;
};

#endif
