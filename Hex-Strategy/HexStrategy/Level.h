#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Tile.h"

class Level
{
public:
	Level(GridVector mapSize);
	~Level();
	typedef std::vector<Tile*> TileRow;
	typedef std::vector<TileRow> TileMap;
	void Update();
	void Render(sf::RenderWindow *window);
private:
	void InternalClear();
	TileMap mTileMap;
	GridVector mMapSize;
};

#endif