#include "particle.h"

Particle::Particle()
	:Position(0.0f), Velosity(0.0f), Color(1.0f), Life(0.0f){}

float Particle::getLife()
{
	return this->Life;
}
void Particle::setLife(float life)
{
	
	this->Life = life;

}

glm::vec2 Particle::getPosition()
{

	return this->Position;

}


void Particle::setPosition(glm::vec2 position)
{

	this->Position = position;

}


glm::vec2 Particle::getVelosity()
{

	return this->Velosity;

}


void Particle::setVelosity(glm::vec2 velosity)
{

	this->Velosity = velosity;

}


glm::vec4 Particle::getColor()
{

	return this->Color;

}


void Particle::setColor(glm::vec4 color)
{

	this->Color = color;

}



