#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Audio.hpp>

#include "entity.h"



class Asteroid: public Entity
{

	static  sf::Texture texture_;
	sf::SoundBuffer buffer_explosion_;
	sf::Sound sound_explosion_;

public:

	Asteroid();

};
#endif // ASTEROID_H
