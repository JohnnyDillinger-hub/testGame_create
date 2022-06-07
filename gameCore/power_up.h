#ifndef POWER_UP_H
#define POWER_UP_H

#include <glad/glad.h>
#include <glm.hpp>

#include "game_object.h"

// Размер бонусного блока
const glm::vec2 POWERUP_SIZE(60.0f, 20.0f);

// Начальная скорость бонусного блока
const glm::vec2 VELOCITY(0.0f, 150.0f);

class PowerUp: public GameObject
{
public:

	std::string Type;
	float Duration;
	bool Activated;

	PowerUp(std::string type, glm::vec3 color, float duration, glm::vec2 position, Texture2D texture);

};

#endif POWER_UP_H