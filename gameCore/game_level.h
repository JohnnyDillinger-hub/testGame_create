#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include <glad/glad.h>
#include <glm.hpp>

#include "game_object.h"
#include "resource_manager.h"

class GameLevel
{
public:

	// Состояние уровня
	std::vector <GameObject> Bricks;

	// Конструктор
	GameLevel() {}

	// Загрузка уровня из файла
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);

	// Рендеринг уровня
	void Draw(SpriteRenderer& renderer);

	// Проверка, пройден ли уровень (все разрушаемые кирпичи должны быть уничтожены)
	bool IsComplited();

private:

	// Инициализация уровня данными из tileData
	void init(std::vector <std::vector <unsigned int>> tileData, unsigned int levelWidth, unsigned int LevelHeight);

};

#endif GAME_LEVEL_H