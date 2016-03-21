#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML\Graphics.hpp>

class TextureManager
{
public:
	static TextureManager& GetInstance();								//Singleton
	sf::Texture* GetTexture(int textureID);
private:
	TextureManager();													//Singleton
	TextureManager(const TextureManager &textureManager);				//Singleton
	TextureManager& operator=(const TextureManager &textureManager);	//Singleton

	sf::Texture mTileTexture,
		mMercenaryTexture,
		mSelectorBitTexture,
		mArcherTexture,
		mFighterTexture,
		mCavallierTexture,
		mMageTexture,
		mWyvernRiderTexture,
		mBonewalkerSwordTexture,
		mBonewalkerBowTexture,
		mGargoyleTexture,
		mTarvosTexture,
		mRevenantTexture,
		mShamanTexture;
};

#endif