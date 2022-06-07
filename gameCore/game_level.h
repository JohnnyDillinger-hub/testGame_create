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

	// ��������� ������
	std::vector <GameObject> Bricks;

	// �����������
	GameLevel() {}

	// �������� ������ �� �����
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);

	// ��������� ������
	void Draw(SpriteRenderer& renderer);

	// ��������, ������� �� ������� (��� ����������� ������� ������ ���� ����������)
	bool IsComplited();

private:

	// ������������� ������ ������� �� tileData
	void init(std::vector <std::vector <unsigned int>> tileData, unsigned int levelWidth, unsigned int LevelHeight);

};

#endif GAME_LEVEL_H