#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Tile.h"

class Level
{
public:
	Level();
	~Level();
	typedef std::vector<Tile> TileRow;
	typedef std::vector<TileRow> TileMap;
	void Update();
	void Render();
private:
	void InternalClear();
	TileMap mTileMap;
};

#endif