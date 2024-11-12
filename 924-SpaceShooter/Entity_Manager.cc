#include "Entity_Manager.h"

#include <SFML/Graphics/RenderTarget.hpp>

void Entity_Manager::Refresh(float dt, const sf::Vector2u& window_size)
{
	auto removed_elt = std::remove_if(entities_.begin(), entities_.end(), [](const Entity& p) {return p.IsDead();});
	if (removed_elt != entities_.end())
	{
		entities_.erase(removed_elt);
	}
	
}

void Entity_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto myAsteroid& e : entities_)
	{
		target.draw(e);
	}
}
