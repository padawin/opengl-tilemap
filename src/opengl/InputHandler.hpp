#ifndef __GLFW_INPUT_HANDLER__
#define __GLFW_INPUT_HANDLER__

#include <memory>
#include "game/InputHandler.hpp"
#include "Renderer.hpp"

class GLFWInputHandler : public InputHandler {
	private:
	std::shared_ptr<OpenGLRenderer> m_renderer = 0;

	protected:
	InputUpdateResult _processEvents();

	public:
	GLFWInputHandler(std::shared_ptr<OpenGLRenderer> renderer);
	bool isKeyPressed(const int key);
};

#endif
