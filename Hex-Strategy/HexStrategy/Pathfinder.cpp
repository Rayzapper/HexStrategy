#include "Pathfinder.h"
#include "Unit.h"
#include "Tile.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::Pathfinder(TileMap tileMap)
{
	mLevelTileMap = tileMap;
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::Update()
{
	
}

vector<Tile*> Pathfinder::FindPath(GridVector start, GridVector target)
{
	vector<Tile*>
		open,			//Nodes whose F cost has been calculated.
		closed;			//Nodes that have been evaluated.
	Tile *startTile, *targetTile;
	startTile = mLevelTileMap->at(start.y)[start.x];
	targetTile = mLevelTileMap->at(target.y)[target.x];
	startTile->SetPathValues(0, GetDistanceCost(startTile, targetTile));
	open.push_back(startTile);
	bool loop = true, failed = false;

	Tile *current = startTile;
	while (loop && !failed)
	{
		if (open.size() == 0)
		{
			failed = true;
			break;
		}
		current = open[0];
		for (vector<Tile*>::size_type i = 0; i < open.size(); i++)
		{
			if (open[i]->GetPathValues().fCost < current->GetPathValues().fCost)
				current = open[i];
		}

		open.erase(find(open.begin(), open.end(), current));

		closed.push_back(current);

		if (current == targetTile)
		{
			loop = false;
			break;
		}

		for each (Tile* neighbor in current->GetNeighbors())
		{
			int newPathLength = CheckPathLength(current, 0);
			newPathLength += 10;

			if (neighbor->GetTileType() == WALL || find(closed.begin(), closed.end(), neighbor) != closed.end())
				; //Skip
			else if (newPathLength < CheckPathLength(neighbor, 0) || find(open.begin(), open.end(), neighbor) == open.end())
			{
				neighbor->SetPathValues(newPathLength, GetDistanceCost(neighbor, targetTile));
				//if (newPathLength == CheckPathLength(neighbor, 0)) Put a random chance on this to create more random Paths.
				neighbor->SetPathParent(current);

				if (find(open.begin(), open.end(), neighbor) == open.end())
				{
					open.push_back(neighbor);
				}
			}
		}
	}

	vector<Tile*> path;
	if (failed)
	{
		for each (TileRow r in *mLevelTileMap)
		{
			for each (Tile *t in r)
			{
				t->SetPathParent(nullptr);
				t->SetPathValues(0, 0);
			}
		}
		return path;
	}
	path = current->GetPath(path);
	path.push_back(current);

	for each (TileRow r in *mLevelTileMap)
	{
		for each (Tile *t in r)
		{
			t->SetPathParent(nullptr);
			t->SetPathValues(0, 0);
		}
	}

	return path;
}

int Pathfinder::GetDistanceCost(Tile *tile1, Tile *tile2)
{
	int distanceCost = 0, tile1X, tile1Y, tile2X, tile2Y, xDifference, yDifference;

	tile1X = tile1->GetGridPosition().x;
	tile1Y = tile1->GetGridPosition().y;
	tile2X = tile2->GetGridPosition().x;
	tile2Y = tile2->GetGridPosition().y;
	tile1X = tile1X * 2 + (tile1Y % 2);
	tile2X = tile2X * 2 + (tile2Y % 2);

	xDifference = abs(tile1X - tile2X);
	yDifference = abs(tile1Y - tile2Y);

	distanceCost = yDifference;
	if (xDifference % 2 == 1)
		distanceCost++;
	distanceCost /= 2;
	if (xDifference % 2 == 0)
		distanceCost += xDifference;
	else
		distanceCost += xDifference - 1;
	if (xDifference >= 2 && yDifference >= 2)
		distanceCost -= xDifference / 2;
	if (distanceCost < xDifference)
		distanceCost = xDifference;

	return distanceCost;
}

int Pathfinder::CheckPathLength(Tile *tile, int oldLength)
{
	int length = oldLength;
	Tile *parent = tile->GetPathParent();
	if (parent != nullptr)
	{
		length += 10;
		length = CheckPathLength(parent, length);
	}
	return length;
}