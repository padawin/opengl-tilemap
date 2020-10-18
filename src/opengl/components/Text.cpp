#include <iostream>
#include "Text.hpp"
#include "opengl/font.hpp"
#include "opengl/texture.hpp"
#include "tilemap/renderers.hpp"

TextComponent::TextComponent(std::shared_ptr<GameObject> owner, std::wstring text, std::string font, unsigned int size) :
	RendererComponent(owner, std::shared_ptr<ObjectRenderer>(new ObjectRenderer()))
{
	long unsigned sizeVertices = text.length() * 30 * sizeof(float);
	float* vertices = (float*) malloc(sizeVertices);

	std::string textureName = font + " " + std::to_string(size);
	Texture* t = texture_get(textureName.c_str());
	if (t == NULL) {
		return;
	}

	m_iAtlasTextureID = t->textureID;

	int n = 0;
	float x = 0.0f;
	float y = 0.0f;
	FontInfo* fi = font_getFontInfo(font, size);
	if (fi == NULL) {
		std::cerr << "Unknown font " << font << " (size: " << size << ")\n";
		return;
	}
	for (unsigned int i = 0; i < text.length(); i++) {
		CharacterInfo c = fi->characterInfo[(int)text[i]];

		float x2 = x + (float) c.bitmapLeft;
		float y2 = -y - (float) c.bitmapTop;
		float w = (float) c.bitmapWidth;
		float h = (float) c.bitmapHeight;

		/* Advance the cursor to the start of the next character */
		x += (float) c.advanceX;
		y += (float) c.advanceY;

		/* Skip glyphs that have no pixels */
		if (c.bitmapWidth == 0 || c.bitmapHeight == 0) {
			continue;
		}

		vertices[n++] = x2;
		vertices[n++] = -y2;
		vertices[n++] = 0.0f;
		vertices[n++] = c.textureXOffset;
		vertices[n++] = 0.0f;

		vertices[n++] = x2 + w;
		vertices[n++] = -y2;
		vertices[n++] = 0.0f;
		vertices[n++] = c.textureXOffset + (float) c.bitmapWidth / (float) t->width;
		vertices[n++] = 0;

		vertices[n++] = x2;
		vertices[n++] = -y2 - h;
		vertices[n++] = 0.0f;
		vertices[n++] = c.textureXOffset;
		vertices[n++] = (float) c.bitmapHeight / (float) t->height;

		vertices[n++] = x2 + w;
		vertices[n++] = -y2;
		vertices[n++] = 0.0f;
		vertices[n++] = c.textureXOffset + (float) c.bitmapWidth / (float) t->width;
		vertices[n++] = 0.0f;

		vertices[n++] = x2;
		vertices[n++] = -y2 - h;
		vertices[n++] = 0.0f;
		vertices[n++] = c.textureXOffset;
		vertices[n++] = (float) c.bitmapHeight / (float) t->height;

		vertices[n++] = x2 + w;
		vertices[n++] = -y2 - h;
		vertices[n++] = 0.0f;
		vertices[n++] = c.textureXOffset + (float) c.bitmapWidth / (float) t->width;
		vertices[n++] = (float) c.bitmapHeight / (float) t->height;
	}

	m_renderer->init();
	m_renderer->setShaderProgram("text");
	m_renderer->setVertices(vertices, (int) sizeVertices);
	free(vertices);
}

void TextComponent::render(std::shared_ptr<Camera> camera) {
	m_renderer->setUniform("isUI", m_bIsUI);
	m_renderer->setTexture("atlas", m_iAtlasTextureID);
	m_renderer->setUniform("color", m_color);
	RendererComponent::render(camera);
}

void TextComponent::setColor(glm::vec3 color) {
	m_color = color;
}

void TextComponent::setUI() {
	m_bIsUI = true;
}
