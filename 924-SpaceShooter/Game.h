#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>


#include "enemy_manager.h"
#include "asteroid_manager.h"
#include "projectile_manager.h"
#include "SpaceShip.h"
#include "enemy.h"

class Game
{

private:
	sf::RenderWindow window_;
	sf::Font font;
	sf::Text text_game_over;
	sf::Text text_hp;
	sf::Text text_score;

	sf::Music background_music;
	sf::Music game_over_music;
	float game_over_cooldown_;


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
	int score = 0;
	float hit_cooldown = 0;
public:
	Game();
	void Loop();
	void SoundLaserEnd();
};


#endif // GAME_H
