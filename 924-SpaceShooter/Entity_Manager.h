#ifndef	ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include <vector>
#include"entity.h"
class Entity_Manager
{
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<Entity>entities_;
public:
	void Refresh(float dt, const sf::Vector2u& window_size);

};
#endif
