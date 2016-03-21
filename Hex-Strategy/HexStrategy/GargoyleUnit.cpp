#include "GargoyleUnit.h"

GargoyleUnit::GargoyleUnit(GridVector gridVector, int team)
	: Unit(10, gridVector, team)
{
	mUnitClasses.push_back(CAVALRY);
	mUnitClasses.push_back(FLIER);
	SetBaseStats();
	mBaseHP = 14;
	mUnitHP = mBaseHP;
	mAttackDamage = 7;
}

GargoyleUnit::~GargoyleUnit()
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