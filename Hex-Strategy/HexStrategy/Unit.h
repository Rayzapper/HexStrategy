#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <iostream>

class Tile;

enum UnitType
{
	INFANTRY,
	MAGE,
	CAVALRY,
	FLIER
};

class Unit : public Entity
{
public:
	Unit(int textureID, GridVector gridVector, int team);
	~Unit();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
	void SetGridPosition(GridVector position);
	void SetCurrentTile(Tile *tile);
	void SetMouseover(bool mouseover);
	void SetMoving(bool moving);
	void SetMovingUp(bool moving);
	void SetMovingDown(bool moving);
	void SetMovingLeft(bool moving);
	void SetMovingRight(bool moving);
	GridVector GetGridPosition() const;
	int GetMovementRange() const;
protected:
	void SetBaseMovement();
	static const int mTileSize = 32;
	int mTeamNumber;
	GridVector mGridVector, mSpriteAnimationVector = GridVector(0, 1), mSpriteSize;
	Tile *mCurrentTile;
	bool mMoving, mMouseover, mMovingUp, mMovingDown, mMovingLeft, mMovingRight;
	int mAnimationDirection = 1;
	float mAnimationSpeed = 1.0;
	sf::Clock mAnimationClock, mSubAnimationClock;
	int mBaseMovementRange = 5;
	vector<UnitType> mUnitTypes;
};

#endif