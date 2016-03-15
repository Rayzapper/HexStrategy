#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(int textureID)
{
	mTexture = TextureManager::GetInstance().GetTexture(textureID);
	mSprite.setTexture(*mTexture);
}

Entity::~Entity()
{

}

void Entity::ChangeTexture(int textureID)
{
	mTexture = TextureManager::GetInstance().GetTexture(textureID);
	mSprite.setTexture(*mTexture);
}