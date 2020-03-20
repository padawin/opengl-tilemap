#include <string>
#include <limits.h> // PATH_MAX
#include <stdlib.h> // realpath
#include <libgen.h> // dirname
#include <iostream>
#include <memory> // shared_ptr

#include "game/config.hpp"
#include "game/Game.hpp"
#include "game/StateMachine.hpp"
#include "game/SceneState.hpp"
#include "game/UserActions.hpp"

#include "opengl/InputHandler.hpp"
#include "opengl/Renderer.hpp"
#include "opengl/shader.hpp"
#include "opengl/texture.hpp"

#include "tilemap/scene/Game.hpp"

const char* WINDOW_TITLE = "Learn OpenGL";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

bool _setBinaryPath(int argc, char* args[]);

int main(int argc, char* args[]) {
	setlocale(LC_ALL,"");
	time_t t;
	srand((unsigned int) time(&t));

	if (!_setBinaryPath(argc, args)) {
		return 1;
	}

	std::shared_ptr<OpenGLRenderer> renderer(new OpenGLRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false));
	std::shared_ptr<GLFWInputHandler> inputHandler(new GLFWInputHandler(renderer));
	UserActions userActions(inputHandler);

	std::string controlsMapping = config_getBinPath() + "/../config/playercontrolsmapping.txt";
	int actionsSet = userActions.setActionsFromFile(controlsMapping.c_str());
	if (actionsSet != 0) {
		std::cerr << "An error occurred while loading the player controls mapping: " << actionsSet << "\n";
		return actionsSet;
	}

	StateMachine<SceneState> stateMachine = StateMachine<SceneState>();
	Game g(stateMachine, renderer, inputHandler);
	if (g.init()
		&& shader_loadPrograms()
		&& texture_loadAll()
	) {
		stateMachine.pushState(new GameScene(userActions));
		g.mainLoop();
	}

	g.shutdown();
	return 0;
}

bool _setBinaryPath(int argc, char* args[]) {
	char binaryPath[PATH_MAX];
	char *res = realpath(dirname(args[argc - argc]), binaryPath);
	if (!res) {
		return false;
	}

	config_setBinPath(binaryPath);
	return true;
}
