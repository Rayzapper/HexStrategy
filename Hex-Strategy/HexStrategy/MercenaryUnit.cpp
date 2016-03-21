#include "MercenaryUnit.h"

MercenaryUnit::MercenaryUnit(GridVector gridVector, int team)
	: Unit(1, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	SetBaseStats();
	mBaseHP = 10;
	mUnitHP = mBaseHP;
	mAttackDamage = 5;
}

MercenaryUnit::~MercenaryUnit()
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