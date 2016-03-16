#include "TextureManager.h"
#include <iostream>

using namespace std;

TextureManager& TextureManager::GetInstance()
{
	static TextureManager textureManager;
	return textureManager;
}

sf::Texture* TextureManager::GetTexture(int textureID)
{
	if (textureID == 0)
		return &mTileTexture;
	else if (textureID == 1)
		return &mMercenaryTexture;
	else if (textureID == 2)
		return &mSelectorBitTexture;
	else
	{
		cout << "Something just asked for a non existent texture." << endl;
		return nullptr;
	}
}

TextureManager::TextureManager()
{
	if (!mTileTexture.loadFromFile("Resources/Graphics/Tiles_spritesheet.png"))
		cout << "Could not find image Tiles_spritesheet.png." << endl;
	if (!mMercenaryTexture.loadFromFile("Resources/Graphics/Mercenary_spritesheet.png"))
		cout << "Could not find image Mercenary_spritesheet.png." << endl;
	if (!mSelectorBitTexture.loadFromFile("Resources/Graphics/Selector_sprite.png"))
		cout << "Could not find image Selector_sprite.png." << endl;
}