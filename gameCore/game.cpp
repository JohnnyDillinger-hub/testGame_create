#include "game.h"

// ������, ����������� � ��������� ����
SpriteRenderer* Renderer;
GameObject* Player;
BallObject* Ball;
ParticleGenerator* Particles;
PostProcessor* Effects;
TextRenderer* Text;

Game::Game(unsigned int width, unsigned int height)
	:State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{}

Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Ball;
	delete Particles;
	delete Effects;
}

void Game::Init()
{

	// �������� ��������
	ResourceManager::LoadShader("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/shaders/sprite.vs",
		"C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/shaders/particles.vs",
		"C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/shaders/particles.frag", nullptr, "particle");
	ResourceManager::LoadShader("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/shaders/post_processing.vs", 
		"C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/shaders/post_processing.frag", nullptr, "postprocessing");

	// ���������������� ��������
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").Use().SetMatrix4("projection", projection);


	// �������� �������
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/block.png", false, "block");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/particle.png", true, "particle");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/powerup_speed.png", true, "powerup_speed");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/powerup_sticky.png", true, "powerup_sticky");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/powerup_increase.png", true, "powerup_increase");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/powerup_confuse.png", true, "powerup_conuse");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/powerup_chaos.png", true, "powerup_chaos");
	ResourceManager::LoadTexture("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/textures/powerup_passthrough.png", true, "powerup_passthrough");

	// ��������� ����������� ��� ���������� ��������� ����������
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	Particles = new ParticleGenerator(
		ResourceManager::GetShader("particle"),
		ResourceManager::GetTexture("particle"),
		500
	);

	Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);

	// �������� �������
	GameLevel one; one.Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/one.lvl", this->Width, this->Height / 2);
	GameLevel two; two.Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/two.lvl", this->Width, this->Height / 2);
	GameLevel three; three.Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/three.lvl", this->Width, this->Height / 2);
	GameLevel four; four.Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/four.lvl", this->Width, this->Height / 2);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	// ���������������� ������� ��������
	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));

	// �����
	SoundEngine->play2D("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/audio/breakout.mp3", true);

	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/fonts/ocraext.TTF", 24);

}

bool Game::CheckCollision(GameObject& one, GameObject& two)
{
	// ���������� �� ��� x?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;

	// ���������� �� ��� y?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;

	// ���� ���������� ���������� ������������ ����� ����, �� �� ����� ������������
	return collisionX && collisionY;
}

Game::Collision Game::CheckCollision(BallObject& ball, GameObject& brick)
{

	// ������� ��������� ����� ������ ���������� 
	glm::vec2 center(ball.Position + ball.Radius);

	// ��������� ���������� �� AABB (���������� ������, � ��������� ���� ������)
	glm::vec2 aabb_half_extents(brick.Size.x / 2.0f, brick.Size.y / 2.0f);
	glm::vec2 aabb_center(
		brick.Position.x + aabb_half_extents.x,
		brick.Position.y + aabb_half_extents.y
	);

	// �������� ������ �������� ����� ������� ���������� � ������� AABB
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	// �������� ���������� clamped � AABB_center �� ������� ��������� � ���������� �����, ������� �� ������� AABB
	glm::vec2 closest = aabb_center + clamped;

	// �������� ������ ����� ������� ���������� � ��������� � ��� ������ AABB, ��������� ����� ����� ����� ������� ���� ������ ������� ���������� 
	difference = closest - center;
	
	// ������ "<", � �� "<=", �.�. � ��������� ������ � ����� ������ ���������� ������������ (����� ������� �������� ���� �����) ���������� ��������� ������������
	if (glm::length(difference) < ball.Radius)
	{
		return std::make_tuple(true, VectorDirection(difference), difference);
	}
	else
	{
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
	}
	
}

bool Game::ShouldSpawn(unsigned int chance)
{

	unsigned int random = rand() % chance;

	return random == 0;

}

void Game::SpawnPowerUps(GameObject& block)
{

	if (ShouldSpawn(75)) // ���� 1 �� 75
		this->PowerUps.push_back(
			PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(
			PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(
			PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(
			PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
	if (ShouldSpawn(35)) // ���������� ������ ������ ���������� ����
		this->PowerUps.push_back(
			PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
	if (ShouldSpawn(35))
		this->PowerUps.push_back(
			PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));

}

// ��������� � ����� ����������� ������� ������ 
// ���������� ���������� �� �������� ���������� ������������
Direction Game::VectorDirection(glm::vec2 target)
{

	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// �����
		glm::vec2(1.0f, 0.0f),	// ������ 
		glm::vec2(0.0f, -1.0f),	// ����
		glm::vec2(-1.0f, 0.0f)	// �����
	};

	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}

	return (Direction)best_match;

}

void Game::ResetLevel()
{
	if (this->Level == 0)
		this->Levels[0].Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/one.lvl", this->Width, this->Height / 2);
	else if (this->Level == 1)
		this->Levels[1].Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/two.lvl", this->Width, this->Height / 2);
	else if (this->Level == 2)
		this->Levels[2].Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/three.lvl", this->Width, this->Height / 2);
	else if (this->Level == 3)
		this->Levels[3].Load("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/levels/four.lvl", this->Width, this->Height / 2);

	this->Lives = 3;
}

void Game::ResetPlayer()
{
	// ����� ��������� ������/�������
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

// �������� ������������
void Game::DoCollisions()
{
	// ���������� ������ ���� (*��������� ���������� ����������*)
	for (GameObject& box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision)) // ���� ��������� ������������
			{
				// ��������� ������ (���� �� �� �������)
				if (!box.IsSolid)
				{

					box.Destroyed = true;
					this->SpawnPowerUps(box);
					SoundEngine->play2D("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/audio/bleep.mp3", false);

				}
				else
				{   // ���� �� ������ - �������, �� ���������� ������ ������
					ShakeTime = 0.05f;
					Effects->SetShake(true);
					SoundEngine->play2D("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/audio/solid.wav", false);
				}

				// ��������� ������������
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (!(Ball->PassThrough && !box.IsSolid)) // ���� ����������� ������ "Pass-Through", �� ��������� ��������� ������������ �� ����������� �������� 
				{
					if (dir == LEFT || dir == RIGHT) // �������������� ������������
					{
						Ball->Velocity.x = -Ball->Velocity.x; // �������� �������������� ��������

						// �����������
						float penetration = Ball->Radius - std::abs(diff_vector.x);
						if (dir == LEFT)
							Ball->Position.x += penetration; // ������� ��� ������� ������
						else
							Ball->Position.x -= penetration; // ������� ��� ������� �����
					}
					else // ������������ ������������
					{
						Ball->Velocity.y = -Ball->Velocity.y; // �������� ������������ ��������

						// �����������
						float penetration = Ball->Radius - std::abs(diff_vector.y);
						if (dir == UP)
							Ball->Position.y -= penetration; // ������� ��� ������� �����
						else
							Ball->Position.y += penetration; // ������� ��� ������� ����
					}
				}
			}
		}

	}

	for (PowerUp& powerUp : this->PowerUps)
	{

		if (!powerUp.Destroyed)
		{
			// ������� ���������, ������ �� ����� ������� ���� ���� � ���� ��� ���, �� ��������� ��� ���������������� � ����������
			if (powerUp.Position.y >= this->Height)
				powerUp.Destroyed = true;

			if (CheckCollision(*Player, powerUp))
			{	// ������������ � �������� ������, ���������� �����
				ActivatePowerUp(powerUp);
				powerUp.Destroyed = true;
				powerUp.Activated = true;
				SoundEngine->play2D("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/audio/powerup.wav", false);
			}
		}
	}

	// �������� ������������ ��� ������� ������ (���� ��� �� ������������ �� ���)
	Collision result = CheckCollision(*Ball, *Player);

	if (!Ball->Stuck && std::get<0>(result))
	{

		// �������, � ����� ����� ��� �������� � �����, � � ����������� �� ����� �������� ��������
		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2.0f);

		// � ��������������� ������� �����������
		float strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		// Ball->Velocity.y = -Ball->Velocity.y;
		// ����� �������� ������� �������� �� ��������������� ��� ������ ���� ���������� (�������� �� �������� ������ ��������, ����� �������� �������� �� ��������)
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); 

		// ������� �������� "������ �������"
		Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);

		Ball->Stuck = Ball->Sticky;
		SoundEngine->play2D("C:/user/programming/repos_VS2019/game_testCreated/game_testCreated/audio/bleep.wav", false);

	}

}

void Game::ActivatePowerUp(PowerUp& powerUp)
{

	if (powerUp.Type == "speed")
	{
		Ball->Velocity *= 1.2;
	}
	else if (powerUp.Type == "sticky")
	{
		Ball->Sticky = true;
		Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
	}
	else if (powerUp.Type == "pass-through")
	{
		Ball->PassThrough = true;
		Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
	}
	else if (powerUp.Type == "pad-size-increase")
	{
		Player->Size.x += 50;
	}
	else if (powerUp.Type == "confuse")
	{
		if (!Effects->GetChaos())
			Effects->SetConfuse(true); // ������������ ��� �������, ��� � ������� ������ �� ��� ����������� ������ "�����"
	}
	else if (powerUp.Type == "chaos")
	{
		if (!Effects->GetConfuse())
			Effects->SetChaos(true);
	}

}

void Game::UpdatePowerUps(float dt)
{

	for (PowerUp& powerUp : this->PowerUps)
	{

		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated)
		{

			powerUp.Duration -= dt;

			if (powerUp.Duration <= 0.0f)
			{
				// ������� ����� �� ������ (� ���������� �� ����� ������)
				powerUp.Activated = false;

				// ������������ �������
				if (powerUp.Type == "sticky")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
					{
						// ���������� ������ � ��� ������, ���� ������ ������� ������ ������� ���� "Sticky" �� ������������
						Ball->Sticky = false;
						Player->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "pass-through")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
					{
						// C��������� ������ � ��� ������, ���� ������ ������� ������ ������� ���� "Pass-Through" �� ������������
						Ball->PassThrough = false;
						Ball->Color = glm::vec3(1.0f);
					}
				}
				else if (powerUp.Type == "confuse")
				{
					if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
					{
						// ���������� ������ � ��� ������, ���� ������ ������� ������ ������� ���� "Confuse" �� ������������
						Effects->SetConfuse(false);
					}
				}
				else if (powerUp.Type == "chaos")
				{
					if (!this->IsOtherPowerUpActive(this->PowerUps, "chaos"))
					{
						// ���������� ������ � ��� ������, ���� ������ ������� ������ ������� ���� "Chaos" �� ������������
						Effects->SetChaos(false);
					}
				}
			}

		}

	}

	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(), [](const PowerUp& powerUp) {return powerUp.Destroyed && !powerUp.Activated; }), this->PowerUps.end());

}

bool Game::IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
{

	for (const PowerUp& powerUp : powerUps)
	{
		if (powerUp.Activated)
		{
			if (powerUp.Type == type)
			{
				return true;
			}
		}
	}

	return false;

}

void Game::Update(float dt)
{

	Ball->Move(dt, this->Width);

	this->DoCollisions();

	Particles->Update(dt, *Ball, 2, glm::vec2(Ball->Radius / 2.0f));

	// ���������� �������
	this->UpdatePowerUps(dt);

	// ������ �� ��� ������ ������� ����?
	if (Ball->Position.y >= this->Height)
	{

		--this->Lives;

		if (this->Lives == 0)
		{
			this->ResetLevel();
			this->State = GAME_MENU;
		}

		this->ResetPlayer();
	}

	if (ShakeTime > 0.0f)
	{
		this->ShakeTime -= dt;
		if (this->ShakeTime <= 0.0f)
			Effects->SetShake(false);
	}

}

// ����� ���������� ��������
void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;

		// ���������� �������
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
			{
				Player->Position.x -= velocity;
				if (Ball->Stuck)
					Ball->Position.x -= velocity;
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
			{
				Player->Position.x += velocity;
				if (Ball->Stuck)
					Ball->Position.x += velocity;
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			Ball->Stuck = false;

		}
	}

	if (this->State == GAME_MENU)
	{
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
		{
			this->State = GAME_ACTIVE;
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}
		if (this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W])
		{
			this->Level = (this->Level + 1) % 4;
			this->KeysProcessed[GLFW_KEY_W] = true;
		}
		if (this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S])
		{
			if (this->Level > 0)
				--this->Level;
			else
				this->Level = 3;
			this->KeysProcessed[GLFW_KEY_S] = true;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE || this->State == GAME_MENU)
	{

		Effects->BeginRender();
		// ��������� ����
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

		// ��������� ������
		this->Levels[this->Level].Draw(*Renderer);

		// ��������� �������
		Player->Draw(*Renderer);


		// ������������ ������	
		Particles->Draw();

		// ��������� ����
		Ball->Draw(*Renderer);

		// ��������� �������
		for (PowerUp& powerUp : this->PowerUps)
			if (!powerUp.Destroyed)
				powerUp.Draw(*Renderer);

		// ���������� ���������� � ��������������-����������
		Effects->EndRender();

		// ���������� ���������� � ��������������-����������
		Effects->Render(glfwGetTime());

		std::stringstream ss; ss << this->Lives;
		Text->RenderText("Lives:" + ss.str(), 5.0f, 5.0f, 1.0f);
	}

	if (this->State == GAME_MENU)
	{
		Text->RenderText("Press ENTER to start", 250.0f, Height / 2, 1.0f);
		Text->RenderText("Press W or S to select level", 245.0f, Height / 2 + 20.0f, 0.75f);
	}
}