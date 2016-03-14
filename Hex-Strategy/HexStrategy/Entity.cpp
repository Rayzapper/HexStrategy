#include "Entity.h"

Entity::Entity(int textureID)
{
	mTexture = mTextureManager->GetTexture(textureID);
}

Entity::~Entity()
{

}

void Entity::Initialize()
{
	TextureManager &textureManager = TextureManager::GetInstance();
	mTextureManager = &textureManager;
}
