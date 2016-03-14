#include "TextureManager.h"

TextureManager& TextureManager::GetInstance()
{
	static TextureManager textureManager;
	return textureManager;
}

sf::Texture* TextureManager::GetTexture(int textureID)
{
	
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	InternalClear();
}

void TextureManager::InternalClear()
{

}
