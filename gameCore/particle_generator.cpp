#include "particle_generator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount)
	:shader(shader), texture(texture), amount(amount)
{
	this->init();
}

void ParticleGenerator::init()
{

	unsigned int VBO;

	float particle_quad[] = {

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f

	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);

	// заполнеяем буфер меша
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	// Настройка атрибутов меша
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	// По умолчанию создаем частицы в количестве "this->amount" штук
	for (unsigned int i = 0; i < this->amount; ++i)
		this->particles.push_back(Particle());

}

unsigned int ParticleGenerator::firstUnusedParticle()
{
	// Сначала проводим поиск, начиная с последней использованной частицы (как правило, результат возвращается почти мгновенно)
	for (unsigned int i = lastUsedParticle; i < this->amount; ++i)
	{
		if (this->particles[i].getLife() <= 0.0f)
		{
			this->lastUsedParticle = i;
			return i;
		}
	}

	// В противном случае выполняем линейный поиск
	for (unsigned int i = 0; i < this->lastUsedParticle; ++i)
	{
		if (this->particles[i].getLife() <= 0.0f) {
			this->lastUsedParticle = i;
			return i;
		}
	}

	// Все частицы еще "живые", поэтому перезаписываем первую (обратите внимание, что если программа
	// неоднократно попадает в данный вариант событий, то следует зарезервировать больше частиц)
	this->lastUsedParticle = 0;
	return 0;

}

void ParticleGenerator::Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset)
{

	for (unsigned int i = 0; i < newParticles; ++i)
	{

		int unusedParticle = this->firstUnusedParticle();
		this->respawnParticle(this->particles[unusedParticle], object, offset);

	}

	for (unsigned int i = 0; i < this->amount; ++i)
	{
		Particle &p = this->particles[i];
		p.setLife(p.getLife() - dt); // уменьшаем время жизни
		if (p.getLife() > 0.0f)
		{   // если частица жива, то обновляем её
			p.setPosition(p.getPosition() -= p.getVelosity() * dt);

			glm::vec4 color = p.getColor();
			color.a -= dt * 2.5f;
			p.setColor(color);
		}
	}

}

void ParticleGenerator::Draw()
{
	// Используем аддитивный режим смешивания для придания эффекта свечения
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	this->shader.Use();

	for (Particle particle : this->particles)
	{

		if (particle.getLife() > 0.0f)
		{
			this->shader.SetVector2f("offset", particle.getPosition());
			this->shader.SetVector4f("color", particle.getColor());
			this->texture.Bind();
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}

	// Не забываем сбросить режим смешивания к изначальным настройкам
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset)
{
	float random = ((rand() % 100) - 50) / 10.0f;
	float rColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.setPosition(object.Position + random + offset);
	particle.setColor(glm::vec4(rColor, rColor, rColor, 1.0f));
	particle.setLife(1.0f);
	particle.setVelosity(object.Velocity * 0.1f);
}