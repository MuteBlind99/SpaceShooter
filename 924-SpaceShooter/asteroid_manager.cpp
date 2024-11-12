#include "asteroid_manager.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>


void AsteroidManager::Refresh(float dt, const sf::Vector2u& window_size)
{
	spawn_dt_ += dt;
	if (spawn_dt_>0.75)
	{
		asteroids_.emplace_back();

		//Seed with a real random value , if available
		std::random_device rn_device;

		//Choose a random mean between 1 and 6
		std::default_random_engine engine(rn_device());
		std::uniform_real_distribution<float>uniform_dist(0, window_size.y);

		asteroids_.back().SetPosition(window_size.x, uniform_dist(engine));
		spawn_dt_ = 0;
	}
	auto removed_elt = std::remove_if(
		asteroids_.begin(),
		asteroids_.end(),
		[](const Asteroid& p) {return p.IsDead();});

	if (removed_elt != asteroids_.end())
	{
		asteroids_.erase(removed_elt);
	}

	for (Asteroid& p : asteroids_)
	{
		p.Move(dt, window_size);
	}
}



void AsteroidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& myAsteroid : asteroids_)
	{
		target.draw(myAsteroid);
	}
}
