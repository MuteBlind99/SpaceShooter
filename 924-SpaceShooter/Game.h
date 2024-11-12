#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>

#include "enemy_manager.h"
#include "asteroid_manager.h"
#include "projectile_manager.h"
#include "SpaceShip.h"
#include "enemy.h"

class Game
{

private:
	sf::RenderWindow window_;

	ProjectileManager projectiles;
	ProjectileManager enemy_projectiles;

	AsteroidManager asteroid_;
	EnemyManager enemy_manager;

	SpaceShip ship_;

	sf::Clock clock_;

public:
	Game();
	void Loop();
};


#endif // GAME_H
