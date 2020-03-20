#ifndef __OPENGL_RENDERER__
#define __OPENGL_RENDERER__

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <string>

#include "game/Renderer.hpp"

class Game;

class OpenGLRenderer : public Renderer {
	private:
	GLFWwindow *m_window = 0;
	int m_iWindowWidth = 0;
	int m_iWindowHeight = 0;
	std::string m_sWindowTitle = "";
	bool m_bFullScreen = false;

	void _initGLFW();
	bool _createWindow();
	bool _initGLAD();

	public:
	OpenGLRenderer(int window_width, int window_height, const char* title, bool fullscreen);
	OpenGLRenderer(OpenGLRenderer const&) = delete;
	void operator=(OpenGLRenderer const&) = delete;
	bool init(void);
	void frame(Game* game) const;
	void shutdown(void);

	bool isKeyPressed(const int key);
};

#endif
