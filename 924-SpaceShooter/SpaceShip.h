#ifndef	SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

class SpaceShip:public sf::Drawable, public sf::Transformable
{
private:
	sf::Texture texture_ship_;
	//std::vector<SpaceShip>ship_;
	sf::Vector2f direction_ship_;
	sf::Sprite sprite_ship_;

	bool is_dead_ = false;

public:
	SpaceShip();
	void Move(float dt, const sf::RenderWindow& window_);
	//void Spawn(sf::Vector2f spawn_position);
	void Refresh(float dt, const sf::RenderWindow& window_);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif