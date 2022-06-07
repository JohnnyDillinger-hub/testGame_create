#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
public:

	SpriteRenderer(const Shader& shader);

	~SpriteRenderer();

	// Рендерим текстурированный прямоугольник по заданному спрайту
	void DrawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	// Состояние рендера
	Shader shader;

	unsigned int quadVAO;

	// Инициализируем и настраиваем атрибуты буфера и атрибуты вершин
	void initRendererData();

};

#endif SPRITE_RENDERER_H