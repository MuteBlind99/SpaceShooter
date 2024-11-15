#include "enemy.h"

#include <SFML/Audio.hpp>


sf::Texture Enemy::texture_;

constexpr float kShootPeriod = 0.01f;
constexpr float kBurstPeriod = 0.3f;

void Enemy::SetDeath()
{
	sound_explosion_.play();
	Entity::SetDeath();
}

Enemy::Enemy()
{
	texture_.loadFromFile("assets\\PNG\\Enemies\\enemyRed1.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height / 2);
	sprite_.setRotation(90);
	sprite_.setScale(0.6f, 0.6f);

	hit_box_.width =static_cast<float> (sprite_.getTextureRect().width) * sprite_.getScale().x;
	hit_box_.height = static_cast<float> (sprite_.getTextureRect().height) * sprite_.getScale().y;

	buffer_shoot_.loadFromFile("assets\\Bonus\\laser5.wav");
	buffer_explosion_.loadFromFile("assets\\synthetic_explosion_1.flac");
	// Associer le buffer à un objet Sound
	sound.setBuffer(buffer_shoot_);
	sound_explosion_.setBuffer(buffer_explosion_);
	direction_ = { -150, 0 };

}


void Enemy::Damage(int damage)
{
	hp_ -= damage;

	if (hp_ <= 0)
	{
		
		SetDeath();
	}
}

void Enemy::Refresh(const double dt)
{
	shoot_dt_ += dt;
	burst_dt_ += dt;
	if (burst_dt_>= kBurstPeriod)
	{
		burst_ready_ = !burst_ready_;
		burst_dt_ = 0;
	}
	if (shoot_dt_>=kShootPeriod && burst_ready_)
	{

		shoot_dt_ = 0;
		is_shoot_ready_ = true;
		
		
	}
	else
	{
		is_shoot_ready_ = false;
	}
}