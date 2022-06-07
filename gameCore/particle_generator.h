#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <glad/glad.h>
#include <glm.hpp>
#include <GLFW/glfw3.h>

#include <vector>

#include "texture.h"
#include "particle.h"
#include "game_object.h"
#include "shader.h"

class ParticleGenerator
{
public:

	ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);

	void Draw();
	void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset);

private:

	std::vector<Particle> particles;

	unsigned int amount;

	Shader shader;
	Texture2D texture;
	unsigned int VAO;
	unsigned int lastUsedParticle = 0;


	void init();

	unsigned int firstUnusedParticle();
	void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset);
	

};

#endif PARTICLE_GENERATOR_H