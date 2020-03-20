#ifndef __PERSPECTIVE_CAMERA__
#define __PERSPECTIVE_CAMERA__

#include <glm/glm.hpp>
#include <memory>
#include "game/Camera.hpp"
#include "game/CameraView.hpp"

class PerspectiveCamera : public Camera {
	private:
	glm::mat4 m_projectionMatrix;
	glm::vec3 m_position;

	public:
	PerspectiveCamera(std::shared_ptr<CameraView> view, float angleDegrees, float screenRatio, float near, float far);
	glm::mat4 getProjection() const;
	glm::vec3 getPosition() const;
};

#endif
