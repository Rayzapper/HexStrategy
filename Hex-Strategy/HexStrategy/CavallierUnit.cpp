#include "CavallierUnit.h"

CavallierUnit::CavallierUnit(GridVector gridVector, int team)
	: Unit(5, gridVector, team)
{
	mUnitClasses.push_back(CAVALRY);
	SetBaseStats();
}

CavallierUnit::~CavallierUnit()
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