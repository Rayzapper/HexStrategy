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
	// Only use sparingly to find paths between two tiles.
	vector<GridVector> FindPath(Tile *start, Tile *target);
	// Only use sparingly to find paths between two tiles.
	bool IsTherePath(Tile *start, Tile *target);
	vector<Tile*> GetMovableTiles(Tile *origin, Unit *unit);
	int GetDistanceCost(Tile *tile1, Tile *tile2);
	int CheckPathLength(Tile *tile, int oldLength);
	vector<Tile*> GetTileCircle(Tile *centerTile, int range);
private:
	bool CanUnitPass(Tile *tile, Unit *unit);
};

#endif