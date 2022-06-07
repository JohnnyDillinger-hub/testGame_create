#ifndef PARTICLE_H
#define PARTICLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Particle
{
public:

	Particle();

	float getLife();
	void setLife(float life);

	glm::vec2 getPosition();
	void setPosition(glm::vec2 position);
	glm::vec2 getVelosity();
	void setVelosity(glm::vec2 velosity);
	glm::vec4 getColor();
	void setColor(glm::vec4 color);



private:

	glm::vec2 Position, Velosity;
	glm::vec4 Color;
	float Life;

};

#endif PARTICLE_H