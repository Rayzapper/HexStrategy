#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "Entity.h"

class UIElement : public Entity
{
public:
	// Texture version
	Entity(int textureID);
	Entity();
	virtual ~Entity();
	virtual void Update();
	virtual void Render(sf::RenderWindow *window);
	void ChangeTexture(int textureID);
protected:
	sf::Vector2f mRenderPosition;
	sf::Texture *mTexture;
	sf::Sprite mSprite;
};

#endif