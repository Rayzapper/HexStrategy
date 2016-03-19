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

struct PathValues
{
	int gCost, //Distance from starting Tile.
		hCost, //Distance from end Tile.
		fCost; //gCost + hCost.
};

class Button;

class Unit;

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
	void SetInhabitant(Unit *unit);
	void SetPathParent(Tile *tile);
	void SetPathValues(int gCost, int hCost);
	void SetHighlight(bool highlight);
	void SetHighlight(sf::Color color, bool highlight);
	GridVector GetGridPosition() const;
	TileType GetTileType() const;
	TerrainType GetTerrainType() const;
	std::vector<Tile*> GetNeighbors() const;
	Unit* GetInhabitant() const;
	bool GetMouseover();
	bool GetClicked();
	bool GetRightClicked();
	Tile* GetPathParent() const;
	PathValues GetPathValues();
	vector<Tile*> GetPath(vector<Tile*> path);
private:
	Button *mButton;
	GridVector mGridPosition;
	TileType mTileType;
	TerrainType mTerrainType = PLAIN;
	std::vector<Tile*> mNeighbors;
	sf::Vector2i mMouseWorldPosition;
	Unit *mInhabitant;
	Tile *mPathParent;
	PathValues mPathValues;
	sf::RectangleShape mTileHighlight;
	bool mHighlighted = false;
};

#endif