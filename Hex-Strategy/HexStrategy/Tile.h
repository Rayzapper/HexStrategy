#ifndef TILE_H
#define TILE_H

#include "Entity.h"
#include "GridVector.h"

enum TileType
{
	FLOOR,
	WALL,
	HOLE
};

enum TerrainType
{
	PLAIN,
	FLOOR,
	RIVER,
	WATER,
	VILLAGE,
	FORT,
	HILL,
	MOUNTAIN,
	FOREST
};

class Tile : public Entity
{
public:
	Tile(GridVector gridPosition);
	virtual void Update();
	virtual void Render();
	void SetTileType(TileType type);
	void SetTerrainType(TerrainType type);
	GridVector GetGridPosition() const;
	TileType GetTileType() const;
	TerrainType GetTerrainType() const;
private:
	GridVector mGridPosition;
	TileType mTileType;
	TerrainType mTerrainType;
};

#endif