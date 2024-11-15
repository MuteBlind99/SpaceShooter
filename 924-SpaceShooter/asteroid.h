#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Audio.hpp>

#include "entity.h"



class Asteroid: public Entity
{

	static  sf::Texture texture_;
	static float rotation_fram_;
	float rotation_ = 0;
public:

	Asteroid();

	void Rotate();

};
#endif // ASTEROID_H
