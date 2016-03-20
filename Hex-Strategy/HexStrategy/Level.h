#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Tile.h"
#include "Unit.h"
#include "Pathfinder.h"

#include "DebugManager.h"

enum SubState
{
	PLAY,
	RIGHTMENU,
	UNITMENU,
	UNITATTACK
};

enum UnitType
{
	MERCENARY,
	FIGHTER,
	ARCHER,
	CAVALLIER,
	WYVERNRIDER,
	MAGE,
	BONEWALKERSWORD,
	BONEWALKERBOW,
	GARGOYLE
};

class Level
{
public:
	Level(GridVector mapSize, sf::RenderWindow *window);
	~Level();
	typedef vector<Tile*> TileRow;
	typedef vector<TileRow> TileMap;
	typedef vector<Unit*> UnitVector;
	void Update(sf::Vector2f mouseWorldPos);
	void Render(sf::RenderWindow *window);
	GridVector GetMouseoverPosition();
	Pathfinder* GetPathfinder();
	void ChangeTurn();
	void PlayUpdate(sf::Vector2f mouseWorldPos);
	void RightMenuUpdate(sf::Vector2f mouseWorldPos);
	void UnitMenuUpdate(sf::Vector2f mouseWorldPos);
private:
	void InternalClear();
	void SpawnUnit(UnitType type, GridVector position, int teamNr);
	void AssignUnitTile(Tile *newTile, Unit *unit);
	TileMap mTileMap;
	GridVector mMapSize, mMouseoverPosition;
	UnitVector mUnitVector;
	Unit *mSelectedUnit, *mMovedUnit;
	Pathfinder mPathfinder;
	vector<Tile*> mMovableTiles, mAttackableTiles;
	bool mUnitIsMoving = false;
	int mPlayerTurn = 0;
	SubState mSubState = PLAY;
	Tile *mMovedFromTile;
};

#endif