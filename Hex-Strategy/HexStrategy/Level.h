#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Tile.h"
#include "Unit.h"
#include "Pathfinder.h"

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
	TileMap mTileMap;
	GridVector mMapSize, mMouseoverPosition;
	UnitVector mUnitVector;
	Unit *mSelectedUnit;
	Pathfinder mPathfinder;
};

#endif