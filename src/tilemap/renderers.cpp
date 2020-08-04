#include "renderers.hpp"
#include "opengl/texture.hpp"

void renderer_initTilemapRenderer(ObjectRenderer *renderer, float width, float height) {
	float vertices[] = {
		// vertices        // texture    // color
		width, height, 0.0f, width, 0.0f, // top right
		0.0f, height, 0.0f, 0.0f, 0.0f, // top left
		width, 0.0f, 0.0f, width, height, // bottom right
		0.0f, 0.0f, 0.0f, 0.0f, height  // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		1, 2, 3    // second triangle
	};

	renderer->init();
	renderer->setShaderProgram("tilemap");
	renderer->setIndexedVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}

void renderer_initSpriteRenderer(ObjectRenderer *renderer) {
	float vertices[] = {
		// vertices        // texture    // color
		1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top right
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top left
		1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom left
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		1, 2, 3    // second triangle
	};

	renderer->init();
	renderer->setShaderProgram("sprite");
	renderer->setIndexedVertices(
		vertices,
		indices,
		(int) sizeof(vertices),
		(int) sizeof(indices)
	);
}
