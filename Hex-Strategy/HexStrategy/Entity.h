#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>

class Entity
{
public:
	virtual ~Entity();
	virtual void Update() = 0;
	virtual void Render() = 0;
protected:
	sf::Vector2f mPosition;
};

#endif