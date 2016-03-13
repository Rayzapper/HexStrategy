#include "TextureManager.h"

TextureManager& TextureManager::GetInstance()
{
	static TextureManager textureManager;
	return textureManager;
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
