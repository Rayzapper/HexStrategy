#include "FighterUnit.h"

FighterUnit::FighterUnit(GridVector gridVector, int team)
	: Unit(4, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	SetBaseStats();
}

FighterUnit::~FighterUnit()
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