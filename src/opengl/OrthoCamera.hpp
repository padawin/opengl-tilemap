#ifndef __ORTHO_CAMERA__
#define __ORTHO_CAMERA__

#include <glm/glm.hpp>
#include <memory>
#include "game/Camera.hpp"
#include "game/CameraView.hpp"

class OrthoCamera : public Camera {
	private:
	glm::mat4 m_projectionMatrix;
	glm::vec3 m_position;

	public:
	OrthoCamera(std::shared_ptr<CameraView> view, float left, float right, float bottom, float top, float near, float far);
	glm::mat4 getProjection() const;
};

#endif
