#include "RevenantUnit.h"

RevenantUnit::RevenantUnit(GridVector gridVector, int team)
	: Unit(12, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	SetBaseStats();
	mBaseHP = 11;
	mUnitHP = mBaseHP;
	mAttackDamage = 5;
}

RevenantUnit::~RevenantUnit()
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