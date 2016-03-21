#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <iostream>

class Tile;

enum UnitClass
{
	INFANTRY,
	CASTER,
	CAVALRY,
	FLIER,
	BOWMAN
};

enum UnitSubState
{
	NOTATTACKING,
	ATTACKING,
	DYING,
	DEAD
};

class Unit : public Entity
{
public:
	Unit();
	Unit(int textureID, GridVector gridVector, int team);
	~Unit();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
	void SetGridPosition(GridVector position);
	void SetCurrentTile(Tile *tile);
	void SetMouseover(bool mouseover);
	void SetSubState(UnitSubState state);
	void SetMoving(bool moving);
	void SetMovingUp(bool moving);
	void SetMovingDown(bool moving);
	void SetMovingLeft(bool moving);
	void SetMovingRight(bool moving);
	void SetMoveAvailable(bool move);
	void SetCurrentPosition(sf::Vector2f position);
	void SetTeam(int team);
	void SetAttackTarget(Unit *target);
	void ChangeHP(int difference);
	GridVector GetGridPosition() const;
	int GetMovementRange() const;
	Tile* GetCurrentTile() const;
	vector<UnitClass> GetUnitClasses() const;
	int GetMinAttackRange() const;
	int GetMaxAttackRange() const;
	UnitSubState GetSubState() const;
	bool GetMoving() const;
	int GetTeam() const;
	bool GetMoveAvailable() const;
	sf::Vector2f GetCurrentPosition() const;
	int GetAttackDamage() const;
	int GetHp() const;
	int GetBaseHp() const;
	void UnitMove(vector<GridVector> orderList);
protected:
	void AttackUpdate();
	void DyingUpdate();
	void SetBaseStats();
	static const int mTileSize = 32;
	int mTeamNumber;
	GridVector mGridVector, mSpriteAnimationVector = GridVector(0, 1), mSpriteSize, *mCurrentTargetTile;
	Tile *mCurrentTile;
	bool mMoving, mMouseover, mMovingUp, mMovingDown, mMovingLeft, mMovingRight;
	int mAnimationDirection = 1;
	float mAnimationSpeed = 1.0;
	sf::Clock mAnimationClock, mSubAnimationClock, mDeathClock;
	int mBaseMovementRange = 5;
	vector<UnitClass> mUnitClasses;
	int mMinAttackRange = 1;
	int mMaxAttackRange = 1;
	vector<GridVector> mMovementList;
	sf::Vector2f mCurrentPosition, mTargetPosition;
	bool mMoveAvailable = true;
	UnitSubState mUnitSubState = NOTATTACKING;
	Unit *mCurrentAttackTarget;
	int mUnitHP = 0, mBaseHP, mAttackDamage;
};

#endif