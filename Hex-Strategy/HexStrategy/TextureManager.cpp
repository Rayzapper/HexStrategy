#include "TextureManager.h"

TextureManager& TextureManager::GetInstance()
{
	static TextureManager textureManager;
	return textureManager;
}

sf::Texture* TextureManager::GetTexture(int textureID)
{
	if (textureID == 0)
		return &mTileTexture;
	else
		return &mMercenaryTexture;
}

TextureManager::TextureManager()
{
	mTileTexture.loadFromFile("Resources/Graphics/Tiles_spritesheet.png");
	mMercenaryTexture.loadFromFile("Resources/Graphics/Mercenary_spritesheet.png");
}