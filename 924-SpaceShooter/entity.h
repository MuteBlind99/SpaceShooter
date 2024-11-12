#ifndef ENTITY_H
#define ENTITY_H


#include <SFML/Graphics/Sprite.hpp>


class Entity :public sf::Drawable, protected sf::Transformable
{

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	
	sf::Vector2f direction_;
	sf::Sprite sprite_;
	sf::FloatRect hit_box_;
	bool is_dead_ = false;

public:

	//Entity();
	void Move(const double dt, const sf::Vector2u& window_size) ;
	bool Intersects(sf::FloatRect hitBox) const;
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f position);

	sf::FloatRect HitBox() { return hit_box_; };

	bool IsDead()const { return is_dead_; }
	virtual void SetDeath() { is_dead_ = true; }

};
#endif

