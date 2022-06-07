#pragma once
#ifndef GAME_H
#define GANE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <irrKlang.h>

#include <vector>

#include "game_level.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include "particle_generator.h"
#include "post_processor.h"
#include "power_up.h"
#include "Settings.h"
#include "text_renderer.h"

using namespace irrklang;

// ������������ ������� ��������� ����
enum GameState { 
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// ��������� ������ ������� ������
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);

// ��������� �������� ����������� ������� ������
const float PLAYER_VELOCITY(500.0f);

// ������ ����
const float BALL_RADIUS = 12.5f;

// ��������� �������� ����
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

// ����� Game �������� ��� ����������� � ���� ��������� � ����������� ����������.
// ���������� ��� ������, ��������� � �����, � ���� ����� ��� �������� ������� � ������� �� �����������
class Game
{
public:
	typedef std::tuple<bool, Direction, glm::vec2> Collision; // <������������?, ����� �����������?, ����� ������� �������� - ��������� �����>

	GameState State;

	bool Keys[1024];
	bool KeysProcessed[1024];

	unsigned int Width, Height;
	unsigned int Level;
	unsigned int Lives;

	std::vector<GameLevel> Levels;
	std::vector<PowerUp> PowerUps;
	
	float ShakeTime = 0.05f;
	
	Game(unsigned int width, unsigned int height);

	~Game();

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	void DoCollisions();

private:

	ISoundEngine* SoundEngine = createIrrKlangDevice();

	bool ShouldSpawn(unsigned int chance);
	bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);
	bool CheckCollision(GameObject& one, GameObject& two);

	void ResetLevel();
	void ResetPlayer();
	void SpawnPowerUps(GameObject &block);
	void ActivatePowerUp(PowerUp &powerUp);
	void UpdatePowerUps(float dt);

	Collision CheckCollision(BallObject& ball, GameObject& brick);
	Direction VectorDirection(glm::vec2 target);
};

#endif GAME_H