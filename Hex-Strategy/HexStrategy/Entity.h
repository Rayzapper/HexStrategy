#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include "GridVector.h"

class Entity
{
public:
	// Texture version
	Entity(int textureID);
	// No Texture version
	Entity();
	virtual ~Entity();
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow *window) = 0;
	void ChangeTexture(int textureID);
protected:
	sf::Vector2f mRenderPosition;
	sf::Texture *mTexture;
	sf::Sprite mSprite;
};

#endif