#include "shader.hpp"
#include "game/config.hpp"
#include "game/utils.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <dirent.h>

typedef std::map<std::string, unsigned int> shadersList;

const char* shadersDir = "/../shaders/";

// These two are used only to create the programs, then they are emptied and not
// used anymore
shadersList _vertexShaders = {};
shadersList _fragmentShaders = {};

std::map<std::string, GLuint> programs = {};

bool _loadShaders(std::string path, GLenum shaderType, shadersList &shaders);
bool _loadShader(std::string shaderName, const char* shaderSrc, GLenum shaderType, GLuint &shader);
bool _loadPrograms(std::string programsFile);
bool _parseProgramLine(
	std::string line,
	std::string &programName,
	std::string &vertexShader,
	std::string &fragmentShader
);
bool _createProgram(std::string programName, std::string vertexShader, std::string fragmentShader);
void _deleteShaders();

bool shader_loadPrograms() {
	std::string baseDir = config_getBinPath() + shadersDir;
	return _loadShaders(baseDir + "/vertex/", GL_VERTEX_SHADER, _vertexShaders)
		&& _loadShaders(baseDir + "/fragment/", GL_FRAGMENT_SHADER, _fragmentShaders)
		&& _loadPrograms(baseDir + "/programs.list");
}

bool _loadShaders(std::string path, GLenum shaderType, shadersList &shaders) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cerr << "Could not open shaders directory: " << path << std::endl;
		return false;
	}

	bool res = true;
	while ((ent = readdir(dir)) != NULL) {
		std::string fname = ent->d_name,
		            fullPath = path + fname,
					shaderSrc;
		if (!utils_isRegularFile(fullPath.c_str())) {
			continue;
		}
		shaderSrc = utils_readFile(fullPath.c_str());
		GLuint shader;
		if (_loadShader(fname, shaderSrc.c_str(), shaderType, shader)) {
			shaders[fname] = shader;
		}
		else {
			res = false;
		}
	}
	closedir(dir);
	return res;
}

bool _loadShader(std::string shaderName, const char* shaderSrc, GLenum shaderType, GLuint &shader) {
	shader = glCreateShader(shaderType);

	// Compile shader
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	// Check shader
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader " << shaderName << " failed compiling:\n" << infoLog << std::endl;
		return false;
	}
	else {
		std::cout << "Shader " << shaderName << " loaded\n";
		return true;
	}
}

bool _loadPrograms(std::string programsFile) {
	std::stringstream ss(utils_readFile(programsFile.c_str()).c_str());
	std::string program;

	bool res = true;
	while (std::getline(ss, program, '\n') ) {
		if (program.length() == 0) {
			continue;
		}

		std::string programName, vertexShader, fragmentShader;
		if (!_parseProgramLine(program, programName, vertexShader, fragmentShader)
			|| !_createProgram(programName, vertexShader, fragmentShader)
		) {
			res = false;
		}
	}

	_deleteShaders();

	return res;
}

bool _parseProgramLine(
	std::string line,
	std::string &programName,
	std::string &vertexShader,
	std::string &fragmentShader
) {
	std::stringstream ssProgram(line.c_str());
	if (!std::getline(ssProgram, programName, ' ')
		|| !std::getline(ssProgram, vertexShader, ' ')
		|| !std::getline(ssProgram, fragmentShader, ' ')
	) {
		std::cerr << "Program line incorrect:\n" << line << std::endl;
		return false;
	}
	else if (_vertexShaders.find(vertexShader) == _vertexShaders.end()) {
		std::cerr << "Unknows vertex shader: " << vertexShader << std::endl;
		return false;
	}
	else if (_fragmentShaders.find(fragmentShader) == _fragmentShaders.end()) {
		std::cerr << "Unknows fragment shader: " << fragmentShader << std::endl;
		return false;
	}
	return true;
}

bool _createProgram(std::string programName, std::string vertexShader, std::string fragmentShader) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, _vertexShaders[vertexShader]);
	glAttachShader(shaderProgram, _fragmentShaders[fragmentShader]);
	glLinkProgram(shaderProgram);
	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Program " << programName << " failed to be loaded:\n" << infoLog << std::endl;
		return false;
	}
	else {
		programs[programName] = shaderProgram;
		return true;
	}
}

void _deleteShaders() {
	for (auto iter : _vertexShaders) {
		glDeleteShader(iter.second);
	}

	for (auto iter : _fragmentShaders) {
		glDeleteShader(iter.second);
	}

	_vertexShaders.clear();
	_fragmentShaders.clear();
}

GLuint shader_getProgram(std::string programName) {
	if (programs.find(programName) == programs.end()) {
		return 0;
	}
	return programs[programName];
}
