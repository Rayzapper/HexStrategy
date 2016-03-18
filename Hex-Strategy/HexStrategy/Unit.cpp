#include "Unit.h"

Unit::Unit(int textureID, GridVector gridVector, int team)
	: Entity(textureID),
	mGridVector(gridVector),
	mTeamNumber(team)
{
	mSpriteSize.x = mTexture->getSize().x / 5;
	mSpriteSize.y = mTexture->getSize().y / 8;
	mSprite.setOrigin(mSpriteSize.x / 2, mSpriteSize.y);
	mSprite.setTextureRect(sf::IntRect(mSpriteAnimationVector.x * mSpriteSize.x, mSpriteAnimationVector.y * mSpriteSize.y, mSpriteSize.x, mSpriteSize.y));
	mRenderPosition = sf::Vector2f(mGridVector.x * 2 * mTileSize + mTileSize / 2 + mTileSize * (mGridVector.y % 2), mGridVector.y * mTileSize / 2 + (mGridVector.x % 2) * 16 + mTileSize);
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
		mSpriteAnimationVector.x = 1;
		mSprite.setScale(2, 2);
		mAnimationSpeed = 1.0;
	}
	else if (mMovingRight)
	{
		mSpriteAnimationVector.x = 1;
		mSprite.setScale(-2, 2);
		mAnimationSpeed = 1.0;
	}
	else if (mMovingDown)
	{
		mSpriteAnimationVector.x = 2;
		mSprite.setScale(2, 2);
		mAnimationSpeed = 0.5;
	}
	else if (mMovingUp)
	{
		mSpriteAnimationVector.x = 3;
		mSprite.setScale(2, 2);
		mAnimationSpeed = 1.0;
	}
	else if (mMouseover)
	{
		if (mSpriteAnimationVector.y <= 0)
		{
			mSpriteAnimationVector.y = 1;
			mAnimationDirection = 1;
		}
		mSpriteAnimationVector.x = 4;
		mSprite.setScale(2, 2);
		mAnimationSpeed = 0.6;
	}
	else
	{
		if (mSpriteAnimationVector.y <= 0)
		{
			mSpriteAnimationVector.y = 1;
			mAnimationDirection = 1;
		}
		mSpriteAnimationVector.x = 0;
		mSprite.setScale(2, 2);
		mAnimationSpeed = 1.0;
	}

	int animationElapsed = mAnimationClock.getElapsedTime().asMilliseconds();
	int subAnimationElapsed = mSubAnimationClock.getElapsedTime().asMilliseconds();

	if (animationElapsed >= 500 * mAnimationSpeed && subAnimationElapsed >= 100 * mAnimationSpeed && !mMoving)
	{
		mSubAnimationClock.restart();
		if ((mSpriteAnimationVector.y <= 1 && mAnimationDirection == -1) || (mSpriteAnimationVector.y >= 3 && mAnimationDirection == 1))
			mAnimationDirection *= -1;
		mSpriteAnimationVector.y += mAnimationDirection;
		if (mSpriteAnimationVector.y >= 3 || mSpriteAnimationVector.y <= 1)
		{
			mAnimationDirection *= -1;
			mAnimationClock.restart();
		}
	}

	if (subAnimationElapsed >= 250 * mAnimationSpeed && mMoving)
	{
		mSubAnimationClock.restart();
		mAnimationClock.restart();
		mSpriteAnimationVector.y++;
		if (mSpriteAnimationVector.y > 3)
			mSpriteAnimationVector.y = 0;
	}

	if (mSpriteAnimationVector.y == 0 && (mSpriteAnimationVector.x == 0 || mSpriteAnimationVector.x == 4))
		mSpriteAnimationVector.y = 1;
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
}

void Unit::SetMouseover(bool mouseover)
{
	mMouseover = mouseover;
}

void Unit::SetMoving(bool moving)
{
	mMoving = moving;
	if (!moving)
	{
		mMovingUp = false;
		mMovingDown = false;
		mMovingLeft = false;
		mMovingRight = false;
	}
}

void Unit::SetMovingUp(bool moving)
{
	mMoving = moving;
	mMovingUp = moving;
	if (moving)
	{
		mMovingLeft = false;
		mMovingRight = false;
		mMovingDown = false;
	}
}

void Unit::SetMovingDown(bool moving)
{
	mMoving = moving;
	mMovingDown = moving;
	if (moving)
	{
		mMovingLeft = false;
		mMovingRight = false;
		mMovingUp = false;
	}
	
}

void Unit::SetMovingLeft(bool moving)
{
	mMoving = moving;
	mMovingLeft = moving;
	if (moving)
	{
		mMovingDown = false;
		mMovingRight = false;
		mMovingUp = false;
	}
}

void Unit::SetMovingRight(bool moving)
{
	mMoving = moving;
	mMovingRight = moving;
	if (moving)
	{
		mMovingLeft = false;
		mMovingDown = false;
		mMovingUp = false;
	}
}

GridVector Unit::GetGridPosition() const
{
	return mGridVector;
}

int Unit::GetMovementRange() const
{
	return mBaseMovementRange;
}

void Unit::SetBaseMovement()
{
	for each (UnitType t in mUnitTypes)
	{
		if (t == MAGE)
			mBaseMovementRange--;
		if (t == CAVALRY)
			mBaseMovementRange += 2;
		if (t == FLIER)
			mBaseMovementRange++;
	}
}