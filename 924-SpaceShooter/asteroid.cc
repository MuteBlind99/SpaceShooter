#include "asteroid.h"

#include <random>
#include <SFML/Graphics/Texture.hpp>
sf::Texture Asteroid::texture_;
float Asteroid::rotation_fram_ = 0.02f;
Asteroid::Asteroid()
{
	texture_.loadFromFile("assets\\PNG\\Meteors\\meteorBrown_big1.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);


	//Seed with a real random value , if available
	std::random_device rn_device;

	//Choose a random mean between 1 and 6
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float>rnd_x(-250, -150);
	std::uniform_real_distribution<float>rnd_y(-50, 50);

	direction_ = { rnd_x(engine), rnd_y(engine) };
}

void Asteroid::Rotate()
{
	rotation_ += rotation_fram_;
		if (rotation_ >= 360)
		{
			rotation_ = 0;
		}
	sprite_.setRotation(rotation_);
}
