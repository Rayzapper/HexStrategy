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
	else if (textureID == 3)
		return &mArcherTexture;
	else if (textureID == 4)
		return &mFighterTexture;
	else if (textureID == 5)
		return &mCavallierTexture;
	else if (textureID == 6)
		return &mMageTexture;
	else if (textureID == 7)
		return &mWyvernRiderTexture;
	else if (textureID == 8)
		return &mBonewalkerSwordTexture;
	else if (textureID == 9)
		return &mBonewalkerBowTexture;
	else if (textureID == 10)
		return &mGargoyleTexture;
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
	if (!mArcherTexture.loadFromFile("Resources/Graphics/Archer_spritesheet.png"))
		cout << "Could not find image Archer_spritesheet.png." << endl;
	if (!mFighterTexture.loadFromFile("Resources/Graphics/Fighter_spritesheet.png"))
		cout << "Could not find image Fighter_spritesheet.png." << endl;
	if (!mCavallierTexture.loadFromFile("Resources/Graphics/Cavallier_spritesheet.png"))
		cout << "Could not find image Cavallier_spritesheet.png." << endl;
	if (!mMageTexture.loadFromFile("Resources/Graphics/Mage_spritesheet.png"))
		cout << "Could not find image Mage_spritesheet.png." << endl;
	if (!mWyvernRiderTexture.loadFromFile("Resources/Graphics/Wyvern_Rider_spritesheet.png"))
		cout << "Could not find image Wyvern_Rider_spritesheet.png." << endl;
	if (!mBonewalkerSwordTexture.loadFromFile("Resources/Graphics/BonewalkerSword_spritesheet.png"))
		cout << "Could not find image BonewalkerSword_spritesheet.png." << endl;
	if (!mBonewalkerBowTexture.loadFromFile("Resources/Graphics/BonewalkerBow_spritesheet.png"))
		cout << "Could not find image BonewalkerBow_spritesheet.png." << endl;
	if (!mGargoyleTexture.loadFromFile("Resources/Graphics/Gargoyle_spritesheet.png"))
		cout << "Could not find image Gargoyle_spritesheet.png." << endl;
}