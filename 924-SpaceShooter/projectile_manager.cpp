#include "projectile_manager.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

void ProjectileManager::Spawn(sf::Vector2f spawn_position)
{
	projectiles_.emplace_back();
	projectiles_.back().setPosition(spawn_position);
}
bool remove_them(Projectile& p)
{
	return p.IsDead();
}

void ProjectileManager::Refresh(float dt, const sf::Vector2u& window_size)
{
	auto removed_elt = std::remove_if(projectiles_.begin(), projectiles_.end(), [](const Projectile& p) {return p.IsDead();});
	if(removed_elt !=projectiles_.end())
	{
		projectiles_.erase(removed_elt);
	}
	for (Projectile& p : projectiles_)
	{
		p.Move(dt, window_size);
	}
	//std::cout << "nb projectiles ? " <<  projectiles_.size<< std::endl;
}

void ProjectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	for (const Projectile& p : projectiles_)
	{
		target.draw(p);
	}

}
