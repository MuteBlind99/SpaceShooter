#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics/Texture.hpp>
#include "entity.h"

class Enemy :public Entity
{
private:
	static sf::Texture texture_;

	int hp_ = 10;
	float shoot_dt_ = 0.f;
	float burst_dt_ = 0.f;
	bool burst_ready_ = false;
	bool is_shoot_ready_ = false;

	
public:
	Enemy();
	sf::Vector2f GetPosition()const { return getPosition(); }
	void SetDeath();
	void Damage(int damage);
	void Refresh(const double dt);

	bool IsShootReady()const { return is_shoot_ready_; }
	double ShootDt()const { return shoot_dt_; }
};
#endif // ENEMY_H