#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>


#include "projectile_manager.h"
#include "SpaceShip.h"

class Game
{

private:
	
	ProjectileManager projectiles;
	SpaceShip ship_;

	sf::Clock clock_;
	float dt_ = 0.016f;
public:
	Game();
	void Loop();
	sf::RenderWindow window_;

};


#endif // GAME_H
