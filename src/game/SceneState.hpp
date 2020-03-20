#ifndef __SCENE_STATE__
#define __SCENE_STATE__

#include "State.hpp"
#include "StateMachine.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"

class SceneState : public State {
	protected:
	UserActions &m_userActions;
	std::shared_ptr<Camera> m_camera = nullptr;
	std::shared_ptr<CameraView> m_cameraView = nullptr;
	float m_fDeltaTime = 0.0f; // Time between current frame and last frame
	double m_fLastFrame = 0.0f; // Time of last frame
	void _update();

	public:
	SceneState(UserActions &userActions);
	virtual void update(StateMachine<SceneState> &stateMachine) = 0;
	void setCamera(std::shared_ptr<Camera> camera);
	void setCameraView(std::shared_ptr<CameraView> cameraView);
};

#endif
