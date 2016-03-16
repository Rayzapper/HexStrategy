#include "Unit.h"

Unit::Unit(int textureID, GridVector gridVector)
	: Entity(textureID),
	mGridVector(gridVector)
{
	int spriteSizeX = mTexture->getSize().x / 5, spriteSizeY = mTexture->getSize().y / 8;
	mSprite.setOrigin(spriteSizeX / 2, spriteSizeY);
	mSprite.setTextureRect(sf::IntRect(0, spriteSizeY, spriteSizeX, spriteSizeY));
	mRenderPosition = sf::Vector2f(mGridVector.x * mTileSize, mGridVector.y * mTileSize / 2);
}

Unit::~Unit()
{

}

void Unit::Update(sf::Vector2f mouseWorldPos)
{

}

void Unit::Render(sf::RenderWindow *window)
{

}

void Unit::SetGridPosition(GridVector position)
{
	mGridVector = position;
}

GridVector Unit::GetGridPosition() const
{
	return mGridVector;
}