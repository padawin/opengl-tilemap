#ifndef __CAMERA_VIEW_FIXED__
#define __CAMERA_VIEW_FIXED__

#include "game/CameraView.hpp"
#include <glm/glm.hpp>

class FixedView : public CameraView {
	private:
	glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, -1.0f);

	public:
	FixedView(glm::vec3 m_direction);
	void update();
};

#endif
