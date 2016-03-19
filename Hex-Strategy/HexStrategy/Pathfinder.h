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
	~Pathfinder();
	void Update();
	vector<Tile*> FindPath(Tile *start, Tile *target);
	bool IsTherePath(Tile *start, Tile *target);
	int GetDistanceCost(Tile *tile1, Tile *tile2);
	int CheckPathLength(Tile *tile, int oldLength);
};

#endif