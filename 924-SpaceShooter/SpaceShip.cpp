#include "SpaceShip.h"
#include "Game.h"
#include <SFML/Graphics/RenderTarget.hpp>


SpaceShip::SpaceShip()
{
	texture_ship_.loadFromFile("assets\\PNG\\playerShip1_red.png");
	sprite_ship_.setTexture(texture_ship_);
	sprite_ship_.setOrigin(texture_ship_.getSize().x/2, texture_ship_.getSize().y/2);
	
	//setRotation(90);
	setScale(0.5,0.5);
}

void SpaceShip::Move(float dt, const sf::RenderWindow& window_)
{
	sprite_ship_.setPosition(sf::Mouse::getPosition(window_).x/getScale().x, sf::Mouse::getPosition(window_).y/getScale().y);


	/*setPosition(getPosition() + direction_ship_ * dt);
	sf::Vector2f position = getPosition();*/
	/*if (position.x < 0 || position.x > window_size.x || position.y < 0 || position.y > window_size.y)
	{
		is_dead_ = true;
	}*/
}

//void SpaceShip::Spawn(sf::Vector2f spawn_position)
//{
//	ship_.emplace_back();
//	ship_.back().setPosition(spawn_position);
//	//sprite_ship_.setPosition(event_ship.mouseButton.x, event_ship.mouseButton.y);
//}

void SpaceShip::Refresh(float dt, const sf::RenderWindow& window_)
{
		Move(dt, window_);
}

void SpaceShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite_ship_, states);
}
