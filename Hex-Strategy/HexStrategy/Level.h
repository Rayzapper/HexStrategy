#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Tile.h"
#include "Unit.h"
#include "Pathfinder.h"

#include "DebugManager.h"

enum UnitType
{
	MERCENARY,
	ARCHER,
	CAVALLIER,
	WYVERNRIDER,
	MAGE,
	BONEWALKERSWORD,
	FIGHTER,
	GARGOYLE
};

class Level
{
public:
	Level(GridVector mapSize);
	~Level();
	typedef vector<Tile*> TileRow;
	typedef vector<TileRow> TileMap;
	typedef vector<Unit*> UnitVector;
	void Update(sf::Vector2f mouseWorldPos);
	void Render(sf::RenderWindow *window);
	GridVector GetMouseoverPosition();
	Pathfinder* GetPathfinder();
private:
	void InternalClear();
	void SpawnUnit(UnitType type, GridVector position, int teamNr);
	void AssignUnitTile(Tile *newTile, Unit *unit);
	TileMap mTileMap;
	GridVector mMapSize, mMouseoverPosition;
	UnitVector mUnitVector;
	Unit *mSelectedUnit;
	Pathfinder mPathfinder;
	vector<Tile*> mMovableTiles;
	bool mUnitIsMoving = false;
};

#endif