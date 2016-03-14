#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
#include "TextureManager.h"

class Entity
{
public:
	Entity(int textureID);
	virtual ~Entity();
	virtual void Update() = 0;
	virtual void Render(sf::RenderWindow *window) = 0;
	static void Initialize();
protected:
	sf::Vector2f mRenderPosition;
	sf::Texture *mTexture;
	sf::Sprite mSprite;
private:
	static TextureManager *mTextureManager;
};

#endif