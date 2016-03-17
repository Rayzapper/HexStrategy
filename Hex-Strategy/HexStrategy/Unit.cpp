#include "Unit.h"
#include "Tile.h"

Unit::Unit(int textureID, GridVector gridVector, int team)
	: Entity(textureID),
	mGridVector(gridVector),
	mTeamNumber(team)
{
	mSpriteSize.x = mTexture->getSize().x / 5;
	mSpriteSize.y = mTexture->getSize().y / 8;
	mSprite.setOrigin(mSpriteSize.x / 2, mSpriteSize.y);
	mSprite.setTextureRect(sf::IntRect(mSpriteAnimationVector.x * mSpriteSize.x, mSpriteAnimationVector.y * mSpriteSize.y, mSpriteSize.x, mSpriteSize.y));
	mRenderPosition = sf::Vector2f(mGridVector.x * mTileSize + mTileSize / 2, mGridVector.y * mTileSize / 2 + mTileSize);
	mSprite.setPosition(mRenderPosition);
	mSprite.setScale(2, 2);
}

Unit::~Unit()
{

}

void Unit::Update(sf::Vector2f mouseWorldPos)
{
	if (mMovingLeft)
	{

	}
	else if (mMovingDown)
		mSpriteAnimationVector.x = 2;
	else if (mMovingUp)
		mSpriteAnimationVector.x = 3;
	if (mAnimationClock.getElapsedTime().asMilliseconds() >= 500)
		if (mSubAnimationClock.getElapsedTime().asMilliseconds() >= 100)
		{
			mSubAnimationClock.restart();
			mSpriteAnimationVector.y += mAnimationDirection;
			if (!mMoving)
			{
				if (mSpriteAnimationVector.y >= 3 || mSpriteAnimationVector.y <= 1)
				{
					mAnimationDirection *= -1;
					mAnimationClock.restart();
				}
			}
			else
				if (mSpriteAnimationVector.y >= 3 || mSpriteAnimationVector.y <= 0)
				{
					mAnimationDirection *= -1;
					mAnimationClock.restart();
				}
		}
	mSprite.setTextureRect(sf::IntRect(mSpriteAnimationVector.x * mSpriteSize.x, mSpriteAnimationVector.y * mSpriteSize.y + mTeamNumber * mSpriteSize.y * 4, mSpriteSize.x, mSpriteSize.y));
}

void Unit::Render(sf::RenderWindow *window)
{
	window->draw(mSprite);
}

void Unit::SetGridPosition(GridVector position)
{
	mGridVector = position;
}

void Unit::SetCurrentTile(Tile *tile)
{
	mCurrentTile = tile;
	SetGridPosition(tile->GetGridPosition());
}

GridVector Unit::GetGridPosition() const
{
	return mGridVector;
}