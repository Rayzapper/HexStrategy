#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <iostream>

class Tile;

class Unit : public Entity
{
public:
	Unit(int textureID, GridVector gridVector, int team);
	~Unit();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
	void SetGridPosition(GridVector position);
	void SetCurrentTile(Tile *tile);
	GridVector GetGridPosition() const;
protected:
	static const int mTileSize = 32;
	int mTeamNumber;
	GridVector mGridVector, mSpriteAnimationVector = GridVector(0, 1), mSpriteSize;
	Tile *mCurrentTile;
	bool mMoving, mSelected, mMovingUp, mMovingDown, mMovingLeft, mMovingRight;
	int mAnimationDirection = 1;
	sf::Clock mAnimationClock, mSubAnimationClock;
};

#endif