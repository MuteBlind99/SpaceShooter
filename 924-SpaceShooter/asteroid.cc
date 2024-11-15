#include "asteroid.h"

#include <random>
#include <SFML/Graphics/Texture.hpp>
sf::Texture Asteroid::texture_;

Asteroid::Asteroid()
{
	texture_.loadFromFile("assets\\PNG\\Meteors\\meteorBrown_big1.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);

	
	buffer_explosion_.loadFromFile("assets\\synthetic_explosion_1.flac");
	// Associer le buffer à un objet Sound
	
	sound_explosion_.setBuffer(buffer_explosion_);

	//Seed with a real random value , if available
	std::random_device rn_device;

	//Choose a random mean between 1 and 6
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float>rnd_x(-250, -150);
	std::uniform_real_distribution<float>rnd_y(-50, 50);

	direction_ = { rnd_x(engine), rnd_y(engine) };
}
