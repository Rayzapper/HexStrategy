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
	Tile(int textureID, GridVector gridPosition, TileType tileType);
	virtual ~Tile();
	virtual void Update();
	virtual void Render(sf::RenderWindow *window);
	void SetTileType(TileType type);
	void SetTerrainType(TerrainType type);
	void SetNeighbor(Tile *neighbor);
	GridVector GetGridPosition() const;
	TileType GetTileType() const;
	TerrainType GetTerrainType() const;
	std::vector<Tile*> GetNeighbors() const;
private:
	GridVector mGridPosition;
	TileType mTileType;
	TerrainType mTerrainType = PLAIN;
	std::vector<Tile*> mNeighbors;
};

#endif