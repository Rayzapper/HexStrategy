#ifndef TILE_H
#define TILE_H

#include "Entity.h"

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

class Button;

class Tile : public Entity
{
public:
	Tile(int textureID, GridVector gridPosition, TileType tileType);
	virtual ~Tile();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
	void SetTileType(TileType type);
	void SetTerrainType(TerrainType type);
	void SetNeighbor(Tile *neighbor);
	GridVector GetGridPosition() const;
	TileType GetTileType() const;
	TerrainType GetTerrainType() const;
	std::vector<Tile*> GetNeighbors() const;
	bool GetMouseover();
	bool GetClicked();
	bool GetRightClicked();
private:
	Button *mButton;
	GridVector mGridPosition;
	TileType mTileType;
	TerrainType mTerrainType = PLAIN;
	std::vector<Tile*> mNeighbors;
	sf::Vector2i mMouseWorldPosition;
};

#endif