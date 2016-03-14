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
	virtual void Render() = 0;
	static void Initialize();
protected:
	sf::Vector2f mPosition;
	static TextureManager *mTextureManager;
	sf::Texture *mTexture;
};

#endif