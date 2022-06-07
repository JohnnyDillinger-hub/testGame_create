#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

// Контейнерный объект, хранящий все состояния, относящиеся к отдельно взятой игровой сущности
class GameObject
{
public:
	
	// Состояние объекта
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool IsSolid;
	bool Destroyed;

	// Состояние рендера
	Texture2D Sprite;

	// Конструкторы
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	// Отрисовка спрайта
	virtual void Draw(SpriteRenderer& renderer);

};

#endif GAME_OBJECT_H