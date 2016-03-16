#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

class UIElement : public Entity
{
public:
	// Texture version
	UIElement(int textureID);
	// No Texture version
	UIElement();
	virtual ~UIElement();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
};

#endif