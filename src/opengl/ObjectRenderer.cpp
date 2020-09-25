#include <iostream>
#include "game/config.hpp"
#include "ObjectRenderer.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ObjectRenderer::_setMode(RenderMode mode) {
	m_mode = mode;
}

ObjectRenderer::ObjectRenderer() :
	m_scale(glm::mat4(1.0f)),
	m_rotation(glm::mat4(1.0f)),
	m_position(glm::mat4(1.0f)),
	m_mode(NO_MODE)
{}

void ObjectRenderer::init() {
	glGenVertexArrays(1, &m_iVAO);
	glGenBuffers(1, &m_iVBO);
	glGenBuffers(1, &m_iEBO);
}

void ObjectRenderer::setIndexedVertices(float* vertices, unsigned int* indices, int verticesSize, int indicesSize) {
	_setMode(RenderMode::INDEXED);
	m_iIndicesCount = indicesSize / (int) sizeof(unsigned int);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(m_iVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize , vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	// Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other VAOs requires a
	// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
	// VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void ObjectRenderer::setVertices(float* vertices, int verticesSize) {
	_setMode(RenderMode::TRIANGLES);
	m_iVerticesCount = verticesSize / (int) sizeof(unsigned int);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(m_iVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize , vertices, GL_STATIC_DRAW);

	// Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other VAOs requires a
	// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
	// VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void ObjectRenderer::setShaderProgram(std::string shaderProgram) {
	m_sShaderProgram = shaderProgram;
}

void ObjectRenderer::setTextures(std::map<const char*, unsigned int> textures) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	glUseProgram(shaderProgram);
	unsigned int currTexture = 0;
	for (auto texture : textures) {
		glActiveTexture(GL_TEXTURE0 + currTexture);
		glBindTexture(GL_TEXTURE_2D, texture.second);
		glUniform1i(glGetUniformLocation(shaderProgram, texture.first), (int) currTexture);
		currTexture++;
	}
}

void ObjectRenderer::setTexture(const char* textureName, unsigned int textureID) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shaderProgram, textureName), 0);
}

void ObjectRenderer::setScale(float x, float y, float z) {
	m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void ObjectRenderer::setRotation(float x, float y, float z) {
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(x), glm::vec3(1.0, 0.0, 0.0));
	trans = glm::rotate(trans, glm::radians(y), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(z), glm::vec3(0.0, 0.0, 1.0));
	m_rotation = trans;
}

void ObjectRenderer::setPosition(float x, float y, float z) {
	m_position = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void ObjectRenderer::setUniform(std::string name, glm::vec3 value) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	int location = glGetUniformLocation(shaderProgram, name.c_str());
	glUseProgram(shaderProgram);
	glUniform3f(location, value.x, value.y, value.z);
}

void ObjectRenderer::setUniform(std::string name, GLuint value) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	int location = glGetUniformLocation(shaderProgram, name.c_str());
	glUseProgram(shaderProgram);
	glUniform1ui(location, value);
}

void ObjectRenderer::setUniform(std::string name, GLfloat value) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	int location = glGetUniformLocation(shaderProgram, name.c_str());
	glUseProgram(shaderProgram);
	glUniform1f(location, value);
}

void ObjectRenderer::setUniform(std::string name, bool value) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	int location = glGetUniformLocation(shaderProgram, name.c_str());
	glUseProgram(shaderProgram);
	glUniform1i(location, value ? 1 : 0);
}

void ObjectRenderer::render(std::shared_ptr<Camera> camera) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());

	float timeValue = (float) glfwGetTime();

	glm::mat4 model = m_position * m_rotation * m_scale * glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where
	// we want to move
	glm::mat4 view = camera->getView();
	glm::mat4 projection = camera->getProjection();

	int screenWidthLocation = glGetUniformLocation(shaderProgram, "screenWidth");
	int screenHeightLocation = glGetUniformLocation(shaderProgram, "screenHeight");
	int timeLocation = glGetUniformLocation(shaderProgram, "currentTime");
	int transformLocation = glGetUniformLocation(shaderProgram, "model");
	int viewLocation = glGetUniformLocation(shaderProgram, "view");
	int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

	glUseProgram(shaderProgram);

	glUniform1f(timeLocation, timeValue);
	glUniform1i(screenWidthLocation, config_getScreenWidth());
	glUniform1i(screenHeightLocation, config_getScreenHeight());
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));


	glBindVertexArray(m_iVAO);
	if (m_mode == RenderMode::INDEXED) {
		glDrawElements(GL_TRIANGLES, m_iIndicesCount, GL_UNSIGNED_INT, 0);
	} else if (m_mode == RenderMode::TRIANGLES) {
		glDrawArrays(GL_TRIANGLES, 0, m_iVerticesCount);
	}
}
