#include "BonewalkerBowUnit.h"

BonewalkerBowUnit::BonewalkerBowUnit(GridVector gridVector, int team)
	: Unit(9, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY),
	mUnitClasses.push_back(BOWMAN);
	SetBaseStats();
	mBaseHP = 8;
	mUnitHP = mBaseHP;
	mAttackDamage = 4;
}

BonewalkerBowUnit::~BonewalkerBowUnit()
{

}

//void MercenaryUnit::Update(sf::Vector2f mouseWorldPos)
//{
//	mSprite.setTextureRect(sf::IntRect(mSpriteAnimationVector.x * mSpriteSize.x, mSpriteAnimationVector.y * mSpriteSize.y, mSpriteSize.x, mSpriteSize.y));
//}

//void MercenaryUnit::Render(sf::RenderWindow * window)
//{
//	window->draw(mSprite);
//}