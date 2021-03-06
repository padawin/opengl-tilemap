#ifndef __OBJECT_RENDERER__
#define __OBJECT_RENDERER__

#include "game/GameObjectRenderer.hpp"
#include "game/Camera.hpp"
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>
#include "glad/glad.h"

enum RenderMode {NO_MODE, TRIANGLES, INDEXED};

class ObjectRenderer : public GameObjectRenderer {
	private:
	unsigned int m_iVAO = 0;
	unsigned int m_iVBO = 0;
	unsigned int m_iEBO = 0;
	int m_iVerticesCount = 0;
	int m_iIndicesCount = 0;
	// Shader program to use
	std::string m_sShaderProgram = "default";

	glm::mat4 m_scale;
	glm::mat4 m_rotation;
	glm::mat4 m_position;

	RenderMode m_mode;

	void _setMode(RenderMode mode);

	public:
	ObjectRenderer();
	virtual ~ObjectRenderer() {}
	void init();
	void setIndexedVertices(float* vertices, unsigned int* indices, int verticesCount, int indicesCount);
	void setVertices(float* vertices, int verticesCount);
	void setShaderProgram(std::string shaderProgram);
	void setTextures(std::map<const char*, unsigned int> textures);
	void setTexture(const char* textureName, unsigned int textureID);

	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setPosition(float x, float y, float z);

	void setUniform(std::string name, glm::vec3 value);
	void setUniform(std::string name, GLuint value);
	void setUniform(std::string name, GLfloat value);
	void setUniform(std::string name, bool value);

	void render(std::shared_ptr<Camera> camera);
};

#endif
