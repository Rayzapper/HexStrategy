#include "TarvosUnit.h"

TarvosUnit::TarvosUnit(GridVector gridVector, int team)
	: Unit(11, gridVector, team)
{
	mUnitClasses.push_back(CAVALRY);
	SetBaseStats();
	mBaseHP = 12;
	mUnitHP = mBaseHP;
	mAttackDamage = 6;
}

TarvosUnit::~TarvosUnit()
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