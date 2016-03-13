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

class Tile : public Entity
{
public:
	Tile(GridVector gridPosition);
	virtual void Update();
	virtual void Render();
	void SetTileType(TileType type);
	GridVector GetGridPosition() const;
	TileType GetTileType() const;
private:
	GridVector mGridPosition;
	TileType mTileType;
};

#endif