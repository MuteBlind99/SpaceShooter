#include "enemy_manager.h"

#include <iostream>
#include <random>
#include <SFML/Graphics/RenderTarget.hpp>

#include "projectile.h"
constexpr float kSpawnPeriod = 0.75f;
constexpr double kShootPeriod = 0.35f;


void EnemyManager::Refresh(float dt, const sf::Vector2u& window_size, ProjectileManager& enemy_missiles_manager)
{
	spawn_dt_ += dt;
	cooldown_shoot += dt;
	if (enemies_.size() < 3 && spawn_dt_ > kSpawnPeriod)
	{
		enemies_.emplace_back();

		// Tirage aléatoire de Y
		// // Seed with a real random value, if available
		std::random_device rn_device;
		// Choose a random mean between 1 and 6
		std::default_random_engine engine(rn_device());
		std::uniform_real_distribution<float> uniform_dist(0, window_size.y);

		enemies_.back().SetPosition(window_size.x, uniform_dist(engine));

		spawn_dt_ = 0;
	}

	// Cleaning unused projectiles
	auto removed_elt = std::remove_if(
		enemies_.begin(),
		enemies_.end(),
		[](const Enemy& e) {return e.IsDead(); }
	);

	if (removed_elt != enemies_.end())
	{
		enemies_.erase(removed_elt);
	}

	// Move remaining projectiles
	for (auto& e : enemies_)
	{
		e.Move(dt, window_size);
		e.Refresh(dt);
		if (e.IsShootReady())
		{

			if (cooldown_shoot >= kShootPeriod)
			{
				enemy_missiles_manager.Spawn(e.GetPosition(), { -750, 0 });
				cooldown_shoot = 0;
			}

		}
	}
}

void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Move remaining projectiles
	for (auto& e : enemies_)
	{
		target.draw(e);
	}
}
