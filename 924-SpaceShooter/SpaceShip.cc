#include "SpaceShip.h"

#include <iostream>

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

constexpr double kShootPeriod = 0.15f;
SpaceShip::SpaceShip()
{
	texture_ship_.loadFromFile("assets\\PNG\\playerShip1_red.png");

	sprite_ship_.setTexture(texture_ship_);
	sprite_ship_.setOrigin(texture_ship_.getSize().x / 2, texture_ship_.getSize().y / 2);

	//setRotation(90);
	setScale(0.5, 0.5);
}

void SpaceShip::Move(sf::Vector2f direction, const double dt)
{
	/*sprite_ship_.setPosition(sf::Mouse::getPosition(window_).x / getScale().x, sf::Mouse::getPosition(window_).y / getScale().y);

	move(direction_ship_ * kSpeed * dt);*/
	move(direction.x * kSpeed * dt, direction.y * kSpeed * dt);
	UpdateHitbox();
}

void SpaceShip::SetPositon(sf::Vector2u position)
{
	setPosition(sf::Vector2f(position));
}

void SpaceShip::UpdateHitbox()
{
	hit_box_ =sprite_ship_.getGlobalBounds();
	hit_box_.left += getPosition().x;
	hit_box_.top += getPosition().y;
}

void SpaceShip::Refresh(const double dt)
{
	shoot_dt_ += dt;
	if (shoot_dt_ > kShootPeriod)
	{
		is_shoot_ready_ = true;
		shoot_dt_ = 0;
	}
}


void SpaceShip::CheckCollisions(std::vector<Projectile>& projectiles)
{
	for (auto& p : projectiles)
	{
		if (p.IsDead() == false && hit_box_.intersects(p.HitBox()))
		{
			p.SetDeath(); // Death of the projectile --------------------------
			// Starship damages ?????
		}
	}
}

void SpaceShip::CheckCollisions(std::vector<Enemy>& enemies)
{
	for(auto e:enemies)
	{
		if (e.IsDead() == false && hit_box_.intersects(e.HitBox()))
		{
			e.Damage(5);
			// Starship damages ?????
		}
	}
}

void SpaceShip::CheckCollisions(std::vector<Asteroid>& asteroids)
{
	for (auto& a : asteroids)
	{
		if (a.IsDead() == false && hit_box_.intersects(a.HitBox()))
		{
			a.SetDeath(); // Death of the asteroid --------------------------
			// Starship damages ?????
		}
	}
}

void SpaceShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	sf::FloatRect ship_hitbox = HitBox();
	sf::RectangleShape rectangle({ ship_hitbox.width, ship_hitbox.height });
	//rectangle.setOrigin(ship_hitbox.getSize().x , ship_hitbox.getSize().y );
	rectangle.setPosition(HitBox().left, HitBox().top);

	rectangle.setFillColor(sf::Color(255, 255, 255, 0));

	rectangle.setOutlineColor(sf::Color(0, 0, 255, 255));
	rectangle.setOutlineThickness(1);

	target.draw(rectangle);
	target.draw(sprite_ship_, states);
}
