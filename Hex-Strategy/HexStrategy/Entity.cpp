#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(int textureID)
{
	mTexture = TextureManager::GetInstance().GetTexture(textureID);
	mSprite.setTexture(*mTexture);
}

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::ChangeTexture(int textureID)
{
	sf::Texture *texture = TextureManager::GetInstance().GetTexture(textureID);
	mSprite.setTexture(*texture);
}