#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include "asteroid.h"


class AsteroidManager:public sf::Drawable
{
private:
	std::vector<Asteroid>asteroids_;
	
	double spawn_dt_ = 0;

public:
	void Refresh(float dt, const sf::Vector2u& window_size);
	std::vector<Asteroid>& GetEntities() { return asteroids_; }
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif

