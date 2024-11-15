#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include <vector>

#include <SFML/Audio.hpp>

#include "asteroid.h"
#include "enemy.h"
#include "Projectile.h"

class ProjectileManager : public sf::Drawable
{
private:
	std::vector<Projectile>projectiles_;
	double cooldown_dt_ = 0;
	sf::SoundBuffer laser;
	sf::Sound sound_;
	sf::SoundBuffer buffer_explosion_;
	sf::Sound sound_explosion_;
public:
	ProjectileManager();

	std::vector<Projectile>& GetEntities() { return projectiles_; }

	void Spawn(sf::Vector2f spawn_position, sf::Vector2f direction);
	void Refresh(float dt, const sf::Vector2u& window_size);

	void CheckCollisions(std::vector<Asteroid>& asteroids, int& score);
	void CheckCollisions(std::vector<Enemy>& enemies, int& score);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif