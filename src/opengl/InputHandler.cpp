#include "InputHandler.hpp"

GLFWInputHandler::GLFWInputHandler(std::shared_ptr<OpenGLRenderer> renderer) : m_renderer(renderer) {}

bool GLFWInputHandler::isKeyPressed(const int key) {
	return m_renderer->isKeyPressed(key);
}
