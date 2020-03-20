#ifndef __CAMERA__
#define __CAMERA__

#include <glm/glm.hpp>
#include <memory>
#include "CameraView.hpp"

class Camera {
	private:
	std::shared_ptr<CameraView> m_view;

	public:
	Camera(std::shared_ptr<CameraView> view);
	virtual ~Camera() {}

	glm::mat4 getView() const;

	virtual glm::mat4 getProjection() const = 0;
};

#endif
