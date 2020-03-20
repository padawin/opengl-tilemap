#ifndef __CAMERA_VIEW_FOLLOW__
#define __CAMERA_VIEW_FOLLOW__

#include "game/CameraView.hpp"
#include "game/GameObject.hpp"
#include <glm/glm.hpp>
#include <memory>

class FollowView : public CameraView {
	private:
	std::shared_ptr<GameObject> m_target = nullptr;
	glm::vec3 m_positionFromTarget;

	public:
	FollowView(std::shared_ptr<GameObject> target, glm::vec3 positionFromTarget);
	void update();
};

#endif
