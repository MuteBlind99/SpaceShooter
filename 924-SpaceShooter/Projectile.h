#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>



class Projectile : public sf::Drawable, public sf::Transformable
{

private:
	static sf::Texture texture_;
	//sf::Sound sound;
	sf::Vector2f direction_;
	
	sf::Sprite sprite_;
	

	bool is_dead_ = false;
public:
	Projectile();

	void Move(float dt, const sf::Vector2u& window_size);

	bool IsDead()const {return is_dead_;}
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	

};

#endif