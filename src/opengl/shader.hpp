#ifndef __SHADER__
#define __SHADER__

#include <string>
#include "glad/glad.h"

bool shader_loadPrograms();
GLuint shader_getProgram(std::string programName);

#endif
