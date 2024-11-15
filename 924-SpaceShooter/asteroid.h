#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Audio.hpp>

#include "entity.h"



class Asteroid: public Entity
{

	static  sf::Texture texture_;


public:

	Asteroid();

};
#endif // ASTEROID_H
