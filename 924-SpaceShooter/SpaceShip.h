#ifndef	SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "asteroid.h"
#include "enemy.h"
#include "Projectile.h"

constexpr float kSpeed = 500.f;
class SpaceShip :public sf::Drawable, public sf::Transformable
{
private:
	sf::Texture texture_ship_;

	sf::Vector2f direction_ship_;
	sf::Sprite sprite_ship_;
	sf::FloatRect hit_box_;

	double shoot_dt_ = 0.f;
	bool is_shoot_ready_ = false;
	int hp_ = 5;
	bool ship_is_dead = false;
	bool hit_ = false;
	int num_hit_ = 0;
	sf::SoundBuffer buffer_hit;
	sf::Sound sound_hit;;
public:
	SpaceShip();
	void Move(sf::Vector2f direction, const double dt);
	int GetHp() { return hp_; }
	sf::FloatRect HitBox()const { return hit_box_; }
	sf::Vector2f GetPosition() { return getPosition(); }
	bool IsShootReady()const { return is_shoot_ready_; }
	void ShootConfirm() { is_shoot_ready_ = false; }
	bool GetStarshipIsDead() { return ship_is_dead; }
	bool GetHit() { return hit_; }
	void Hit(float& hit_cooldown);

	void SetPositon(sf::Vector2u position);
	/*void Refresh(float dt, const sf::RenderWindow& window_);*/
	void UpdateHitbox();
	void Refresh(const double dt);
	void CheckCollisions(std::vector<Asteroid>& asteroids);
	void CheckCollisions(std::vector<Projectile>& projectiles);
	void CheckCollisions(std::vector<Enemy>& enemies);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif