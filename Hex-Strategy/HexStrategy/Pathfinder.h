#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include "GridVector.h"

using namespace std;

class Tile;
class Unit;

typedef vector<Tile*> TileRow;
typedef vector<TileRow>* TileMap;

class Pathfinder
{
public:
	Pathfinder();
	Pathfinder(TileMap tileMap);
	~Pathfinder();
	void Update();
	vector<Tile*> FindPath(GridVector start, GridVector target);
	int GetDistanceCost(Tile *tile1, Tile *tile2);
	int CheckPathLength(Tile *tile, int oldLength);
private:
	TileMap mLevelTileMap;
};

#endif