#include <iostream>
#include "ObjectRenderer.hpp"
#include "glad/glad.h"
#include "shader.hpp"
#include "texture.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ObjectRenderer::ObjectRenderer() :
	m_scale(glm::mat4(1.0f)),
	m_rotation(glm::mat4(1.0f)),
	m_position(glm::mat4(1.0f))
{}

void ObjectRenderer::init() {
	glGenVertexArrays(1, &m_iVAO);
	glGenBuffers(1, &m_iVBO);
	glGenBuffers(1, &m_iEBO);
}

void ObjectRenderer::setVertices(float* vertices, unsigned int* indices, int verticesSize, int indicesSize) {
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

void ObjectRenderer::setShaderProgram(std::string shaderProgram) {
	m_sShaderProgram = shaderProgram;
}

void ObjectRenderer::setTexture(std::string texture) {
	m_sTexture = texture;
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

void ObjectRenderer::render(std::shared_ptr<Camera> camera) {
	GLuint shaderProgram = shader_getProgram(m_sShaderProgram.c_str());
	GLuint texture = texture_get(m_sTexture.c_str());

	float timeValue = (float) glfwGetTime();

	glm::mat4 model = m_position * m_rotation * m_scale * glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where
	// we want to move
	glm::mat4 view = camera->getView();
	glm::mat4 projection = camera->getProjection();

	int timeLocation = glGetUniformLocation(shaderProgram, "currentTime");
	int transformLocation = glGetUniformLocation(shaderProgram, "model");
	int viewLocation = glGetUniformLocation(shaderProgram, "view");
	int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform1f(timeLocation, timeValue);
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_iVAO);
	// TODO The mode should be configurable
	glDrawElements(GL_TRIANGLES, m_iIndicesCount, GL_UNSIGNED_INT, 0);
}
