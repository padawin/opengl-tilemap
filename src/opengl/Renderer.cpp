#include "Renderer.hpp"
#include "mouse.hpp"
#include "game/Game.hpp"
#include <iostream>
#include <errno.h>
#include <string.h>

OpenGLRenderer::OpenGLRenderer(int width, int height, const char* title, bool fullscreen) :
	m_iWindowWidth(width),
	m_iWindowHeight(height),
	m_sWindowTitle(title),
	m_bFullScreen(fullscreen)
{
}

bool OpenGLRenderer::init(void) {
	_initGLFW();
	if (!_createWindow() || !_initGLAD()) {
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// @NOTE This defines the viewport used by OpenGL IN the window, not
	// the position/geometry of the window in the screen.
	glViewport(0, 0, m_iWindowWidth, m_iWindowHeight);

	return true;
}

void OpenGLRenderer::_initGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
}

bool OpenGLRenderer::_createWindow() {
	GLFWmonitor* monitor = NULL;
	if (m_bFullScreen) {
		monitor = glfwGetPrimaryMonitor();
	}
	// Create window
	m_window = glfwCreateWindow(
		m_iWindowWidth, m_iWindowHeight, m_sWindowTitle.c_str(), monitor, NULL
	);
	if (m_window == NULL) {
		std::cerr << "Failed to create GLFW window: " << strerror(errno) << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_window);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_window, mouse_callback);
	return true;
}

bool OpenGLRenderer::_initGLAD() {
	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD: " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}

void OpenGLRenderer::frame(Game* game) const {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	game->frame();
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void OpenGLRenderer::shutdown(void) {
	glfwTerminate();
}

bool OpenGLRenderer::isKeyPressed(const int key) {
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}
