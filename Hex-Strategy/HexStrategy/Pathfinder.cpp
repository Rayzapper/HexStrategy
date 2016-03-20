#include "Pathfinder.h"
#include "Unit.h"
#include "Tile.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::Update()
{
	
}

vector<GridVector> Pathfinder::FindPath(Tile *start, Tile *target)
{
	vector<Tile*>
		open,			//Nodes whose F cost has been calculated.
		closed;			//Nodes that have been evaluated.
	Tile *startTile, *targetTile;
	startTile = start;
	targetTile = target;
	Unit *unit = startTile->GetInhabitant();
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

			if (!CanUnitPass(neighbor, unit) || find(closed.begin(), closed.end(), neighbor) != closed.end())
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

	vector<GridVector> path;
	if (failed)
	{
		for each (Tile *t in open)
		{
			t->SetPathParent(nullptr);
			t->SetPathValues(0, 0);
		}
		for each (Tile *t in closed)
		{
			t->SetPathParent(nullptr);
			t->SetPathValues(0, 0);
		}
		return path;
	}
	path = current->GetPath(path);
	path.push_back(current->GetGridPosition());

	for each (Tile *t in open)
	{
		t->SetPathParent(nullptr);
		t->SetPathValues(0, 0);
	}
	for each (Tile *t in closed)
	{
		t->SetPathParent(nullptr);
		t->SetPathValues(0, 0);
	}

	return path;
}

bool Pathfinder::IsTherePath(Tile *start, Tile *target)
{
	if (FindPath(start, target).size() == 0)
		return false;
	return true;
}

vector<Tile*> Pathfinder::GetMovableTiles(Tile *origin, Unit *unit)
{
	vector<Tile*> movableTiles, closed, open;
	movableTiles.push_back(origin);
	open.push_back(origin);
	int moveRange = unit->GetMovementRange();
	for (int i = 0; i < moveRange; i++)
	{
		int max = open.size();
		vector<Tile*> temp = open;
		for (int j = 0; j < max; j++)
		{
			Tile *tile = temp[j];
			for each (Tile *neighbor in tile->GetNeighbors())
			{
				if (find(closed.begin(), closed.end(), neighbor) != closed.end() || find(open.begin(), open.end(), neighbor) != open.end())
					; // Skip
				else if (!CanUnitPass(neighbor, unit))
					closed.push_back(neighbor);
				else
				{
					open.push_back(neighbor);
					movableTiles.push_back(neighbor);
				}
			}
			closed.push_back(tile);
			open.erase(find(open.begin(), open.end(), tile));
		}
	}
	return movableTiles;
}

int Pathfinder::GetDistanceCost(Tile *tile1, Tile *tile2)
{
	int distanceCost = 0, tile1X, tile1Y, tile2X, tile2Y, xDifference, yDifference;

	tile1X = tile1->GetGridPosition().x;
	tile1Y = tile1->GetGridPosition().y;
	tile2X = tile2->GetGridPosition().x;
	tile2Y = tile2->GetGridPosition().y;

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

vector<Tile*> Pathfinder::GetTileCircle(Tile *centerTile, int range)
{
	vector<Tile*> circle, closed;
	circle.push_back(centerTile);
	for (int i = 0; i < range; i++)
	{
		vector<Tile*> temp = circle;
		for each (Tile *t in circle)
			closed.push_back(t);
		circle.clear();
		for each (Tile *t in temp)
			for each (Tile *neighbor in t->GetNeighbors())
				if (find(closed.begin(), closed.end(), neighbor) == closed.end() && find(circle.begin(), circle.end(), neighbor) == circle.end())
					circle.push_back(neighbor);
	}
	return circle;
}

bool Pathfinder::CanUnitPass(Tile *tile, Unit *unit)
{
	if (tile->GetTileType() == WALL)
		return false;
	vector<UnitClass> unitClasses = unit->GetUnitClasses();
	if (find(unitClasses.begin(), unitClasses.end(), FLIER) != unitClasses.end())
		return true;
	if (tile->GetTileType() == HOLE)
		return false;
	if (tile->GetInhabitant() != nullptr)
		if (unit->GetTeam() != tile->GetInhabitant()->GetTeam())
			return false;
	return true;
}
