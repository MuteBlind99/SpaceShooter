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

	sf::Texture backgroundTexture;
	
	// Créer un sprite et lui associer la texture
	sf::Sprite backgroundSprite;

	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Game();
	void Loop();
	void SoundLaserEnd();
};


#endif // GAME_H
