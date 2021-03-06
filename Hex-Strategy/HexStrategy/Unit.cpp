#include "Unit.h"

Unit::Unit()
{
	
}

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
	mCurrentPosition = sf::Vector2f(mGridVector.x * mTileSize, mGridVector.y * mTileSize / 2);
	mSprite.setPosition(mRenderPosition);
	mSprite.setScale(2, 2);
}

Unit::~Unit()
{

}

void Unit::Update(sf::Vector2f mouseWorldPos)
{
	if (mMoveAvailable)
		mSprite.setColor(sf::Color::White);
	else
		mSprite.setColor(sf::Color(127, 127, 127, 255));

	if (mUnitSubState != DEAD && mUnitSubState != DYING)
	{
		mUnitSubState = NORMAL;
		if (mUnitHP <= 0)
		{
			mUnitSubState = DYING;
			mHurtAnimationColor = 255;
		}
	}

	if (mUnitSubState == NORMAL)
	{
		SetMoving(!mMovementList.empty());
		if (!mMovementList.empty())
			mCurrentTargetTile = &mMovementList.front();

		if (mCurrentTargetTile != nullptr)
		{
			mTargetPosition = sf::Vector2f(mCurrentTargetTile->x * mTileSize, mCurrentTargetTile->y * mTileSize / 2);
			if (mCurrentPosition.x < mTargetPosition.x)
			{
				SetMovingRight(true);
				mCurrentPosition.x += 4;
				if (mCurrentPosition.x >= mTargetPosition.x)
					mCurrentPosition.x = mTargetPosition.x;
				if (mCurrentPosition.y < mTargetPosition.y)
				{
					mCurrentPosition.y += 2;
					if (mCurrentPosition.y >= mTargetPosition.y)
						mCurrentPosition.y = mTargetPosition.y;
				}
				if (mCurrentPosition.y > mTargetPosition.y)
				{
					mCurrentPosition.y -= 2;
					if (mCurrentPosition.y <= mTargetPosition.y)
						mCurrentPosition.y = mTargetPosition.y;
				}
			}
			else if (mCurrentPosition.x > mTargetPosition.x)
			{
				SetMovingLeft(true);
				mCurrentPosition.x -= 4;
				if (mCurrentPosition.x <= mTargetPosition.x)
					mCurrentPosition.x = mTargetPosition.x;
				if (mCurrentPosition.y < mTargetPosition.y)
				{
					mCurrentPosition.y += 2;
					if (mCurrentPosition.y >= mTargetPosition.y)
						mCurrentPosition.y = mTargetPosition.y;
				}
				if (mCurrentPosition.y > mTargetPosition.y)
				{
					mCurrentPosition.y -= 2;
					if (mCurrentPosition.y <= mTargetPosition.y)
						mCurrentPosition.y = mTargetPosition.y;
				}
			}
			else if (mCurrentPosition.y < mTargetPosition.y)
			{
				SetMovingDown(true);
				mCurrentPosition.y += 4;
				if (mCurrentPosition.y >= mTargetPosition.y)
					mCurrentPosition = mTargetPosition;
			}
			else if (mCurrentPosition.y > mTargetPosition.y)
			{
				SetMovingUp(true);
				mCurrentPosition.y -= 4;
				if (mCurrentPosition.y <= mTargetPosition.y)
					mCurrentPosition = mTargetPosition;
			}

			if (mCurrentPosition == mTargetPosition)
			{
				mMovementList.erase(mMovementList.begin() + 0);
				mCurrentTargetTile = nullptr;
				mGridVector = GridVector(mCurrentPosition.x / mTileSize, mCurrentPosition.y / mTileSize / 2);
			}
		}

		if (mMovingLeft)
		{
			mSpriteAnimationVector.x = 1;
			mSprite.setScale(2, 2);
			mAnimationSpeed = 0.5;
		}
		else if (mMovingRight)
		{
			mSpriteAnimationVector.x = 1;
			mSprite.setScale(-2, 2);
			mAnimationSpeed = 0.5;
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
			mAnimationSpeed = 0.5;
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

		mRenderPosition.x = mCurrentPosition.x + mTileSize / 2;
		mRenderPosition.y = mCurrentPosition.y + mTileSize;
		mSprite.setPosition(mRenderPosition);

		if (mSpriteAnimationVector.y == 0 && (mSpriteAnimationVector.x == 0 || mSpriteAnimationVector.x == 4))
			mSpriteAnimationVector.y = 1;
		mSprite.setTextureRect(sf::IntRect(mSpriteAnimationVector.x * mSpriteSize.x, mSpriteAnimationVector.y * mSpriteSize.y + mTeamNumber * mSpriteSize.y * 4, mSpriteSize.x, mSpriteSize.y));
	}
	else if (mUnitSubState == DYING)
		DyingUpdate();
	else if (mUnitSubState == DAMAGED)
		HurtUpdate();
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

void Unit::SetSubState(UnitSubState state)
{
	mUnitSubState = state;
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

void Unit::SetMoveAvailable(bool move)
{
	mMoveAvailable = move;
}

void Unit::SetCurrentPosition(sf::Vector2f position)
{
	mCurrentPosition = position;
	mRenderPosition.x = mCurrentPosition.x + mTileSize / 2;
	mRenderPosition.y = mCurrentPosition.y + mTileSize;
}

void Unit::SetTeam(int team)
{
	mTeamNumber = team;
}

void Unit::ChangeHP(int difference)
{
	mUnitHP += difference;
	if (mUnitHP < 0) mUnitHP = 0;
	if (mUnitHP != 0 && difference < 0)
	{
		mUnitSubState = DAMAGED;
		mSprite.setColor(sf::Color(255, 0, 0, 255));
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

Tile* Unit::GetCurrentTile() const
{
	return mCurrentTile;
}

vector<UnitClass> Unit::GetUnitClasses() const
{
	return mUnitClasses;
}

int Unit::GetMinAttackRange() const
{
	return mMinAttackRange;
}

int Unit::GetMaxAttackRange() const
{
	return mMaxAttackRange;
}

UnitSubState Unit::GetSubState() const
{
	return mUnitSubState;
}

bool Unit::GetMoving() const
{
	return mMoving;
}

int Unit::GetTeam() const
{
	return mTeamNumber;
}

bool Unit::GetMoveAvailable() const
{
	return mMoveAvailable;
}

sf::Vector2f Unit::GetCurrentPosition() const
{
	return mCurrentPosition;
}

int Unit::GetAttackDamage() const
{
	return mAttackDamage;
}

int Unit::GetHp() const
{
	return mUnitHP;
}

int Unit::GetBaseHp() const
{
	return mBaseHP;
}

void Unit::UnitMove(vector<GridVector> orderList)
{
	mMovementList = orderList;
	mMoving = true;
	mMovementList.erase(mMovementList.begin());
}

void Unit::DyingUpdate()
{
	mHurtAnimationColor -= 4;
	if (mHurtAnimationColor <= 0) mHurtAnimationColor = 0;
	mSprite.setColor(sf::Color(255, mHurtAnimationColor, mHurtAnimationColor, mHurtAnimationColor));
	if (mHurtAnimationColor <= 0)
		mUnitSubState = DEAD;
}

void Unit::HurtUpdate()
{
	mHurtAnimationColor += 10;
	if (mHurtAnimationColor >= 255) mHurtAnimationColor = 255;
	mSprite.setColor(sf::Color(255, mHurtAnimationColor, mHurtAnimationColor, 255));
	if (mHurtAnimationColor >= 255)
	{
		mUnitSubState = NORMAL;
		mHurtAnimationColor = 0;
	}
}

void Unit::SetBaseStats()
{
	for each (UnitClass c in mUnitClasses)
	{
		if (c == CASTER)
		{
			mBaseMovementRange--;
			mMaxAttackRange = 2;
		}
		if (c == CAVALRY)
			mBaseMovementRange += 2;
		if (c == FLIER)
			mBaseMovementRange++;
		if (c == BOWMAN)
		{
			mMinAttackRange = 2;
			mMaxAttackRange = 2;
		}
	}
}