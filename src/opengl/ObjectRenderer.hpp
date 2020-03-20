#ifndef __OBJECT_RENDERER__
#define __OBJECT_RENDERER__

#include "game/GameObjectRenderer.hpp"
#include "game/Camera.hpp"
#include <string>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class ObjectRenderer : public GameObjectRenderer {
	private:
	unsigned int m_iVAO = 0;
	unsigned int m_iVBO = 0;
	unsigned int m_iEBO = 0;
	int m_iIndicesCount = 0;
	// Shader program to use
	std::string m_sShaderProgram = "default";
	std::string m_sTexture = "";

	glm::mat4 m_scale;
	glm::mat4 m_rotation;
	glm::mat4 m_position;

	public:
	ObjectRenderer();
	void init();
	void setVertices(float* vertices, unsigned int* indices, int verticesCount, int indicesCount);
	void setShaderProgram(std::string shaderProgram);
	void setTexture(std::string texture);

	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setPosition(float x, float y, float z);

	void setUniform(std::string name, glm::vec3 value);

	void render(std::shared_ptr<Camera> camera);
};

#endif
