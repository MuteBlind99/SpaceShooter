#include "projectile_manager.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

#include "asteroid.h"
#include "asteroid_manager.h"

constexpr float kCooldown_limit_ = 0.15f;

void ProjectileManager::Spawn(sf::Vector2f spawn_position, sf::Vector2f direction)
{
	
	projectiles_.emplace_back(direction);
	projectiles_.back().SetPosition(spawn_position);
	
}

void ProjectileManager::Refresh(float dt, const sf::Vector2u& window_size)
{

	
	auto removed_elt = std::remove_if(
		projectiles_.begin(),
		projectiles_.end(),
		[](const Projectile& p) {return p.IsDead();});


	if (removed_elt != projectiles_.end())
	{
		projectiles_.erase(removed_elt);
	}
	for (Projectile& p : projectiles_)
	{
		p.Move(dt, window_size);

		p.UpdateAnimation(dt);

	}
	/*std::cout << "nb projectiles ? " <<  projectiles_.size() << '\n';*/
}

void ProjectileManager::CheckCollisions(std::vector<Asteroid>& asteroids)
{
	for (auto& p : projectiles_)
	{
		for (auto& a : asteroids)
		{
			if (p.IsDead()==false && a.IsDead()==false && p.Intersects(a.HitBox()))
			{
				p.SetDeath();
				a.SetDeath();
			}
		}
	}
}

void ProjectileManager::CheckCollisions(std::vector<Enemy>& enemies)
{
	for (auto& p : projectiles_)
	{
		for (auto& e : enemies)
		{
			if (p.IsDead() == false && e.IsDead() == false && p.Intersects(e.HitBox()))
			{
				p.SetDeath();
				e.Damage(1);
			}
		}
	}
}

void ProjectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (const Projectile& p : projectiles_)
	{

		target.draw(p);
	}

}