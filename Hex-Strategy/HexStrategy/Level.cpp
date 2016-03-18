#include "Level.h"
#include <cassert>
#include <iostream>
#include "MercenaryUnit.h"
#include "WyvernRiderUnit.h"
#include "MageUnit.h"
#include "BonewalkerSwordUnit.h"

static const int tileSize = 32;

static sf::Color highlightBlue(100, 100, 255, 127), highlightRed(255, 100, 100, 127), highlightGreen(100, 255, 100, 127);

Level::Level(GridVector mapSize)
	: mMapSize(mapSize)
{
	for (int y = 0; y < mapSize.y; y++)
	{
		TileRow row;
		for (int x = 0; x < mapSize.x; x++)
		{
			TileType tileType = FLOOR;
			if (y <= 1 || x == 0 || y >= mapSize.y - 2 || x == mapSize.x - 1)
				tileType = WALL;
			else if (y % 8 == 4 && x % 4 == 2)
				tileType = HOLE;
			else if (x == 8 && (y > 18 || y < 16))
				tileType = WALL;
			if (y % 2 == 0 && x % 2 == 0)
			{
				row.push_back(new Tile(0, GridVector(x, y), tileType));
			}
			if (y % 2 == 1 && x % 2 == 1)
			{
				row.push_back(new Tile(0, GridVector(x, y), tileType));
			}
		}
		mTileMap.push_back(row);
	}

	mPathfinder = Pathfinder(&mTileMap);

	int evenRowSize = mTileMap[0].size();
	int oddRowSize = mTileMap[1].size();
	int rowAmount = mTileMap.size();
	for (TileMap::size_type y = 0; y < mTileMap.size(); y++)
	{
		for (TileRow::size_type x = 0; x < mTileMap[y].size(); x++)
		{
			Tile *tile = mTileMap[y][x];
			if (y % 2 == 0)
			{
				if (x > 0 && y > 0)
					tile->SetNeighbor(mTileMap[y - 1][x - 1]);
				if (y > 0)
					tile->SetNeighbor(mTileMap[y - 2][x]);
				if (x <= oddRowSize - 1 && y > 0)
					tile->SetNeighbor(mTileMap[y - 1][x]);
				if (x > 0 && y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x - 1]);
				if (y < rowAmount - 2)
					tile->SetNeighbor(mTileMap[y + 2][x]);
				if (x <= oddRowSize - 1 && y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x]);
			}
			else
			{
				tile->SetNeighbor(mTileMap[y - 1][x]);
				if (y > 1)
					tile->SetNeighbor(mTileMap[y - 2][x]);
				if (x < evenRowSize - 1)
					tile->SetNeighbor(mTileMap[y - 1][x + 1]);
				if (y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x]);
				if (y < rowAmount - 2)
					tile->SetNeighbor(mTileMap[y + 2][x]);
				if (x < evenRowSize - 1 && y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x + 1]);
			}
		}
	}

	GridVector unitPlacementVector = GridVector(2, 8);
	Unit *unit = new MercenaryUnit(GridVector(unitPlacementVector.x, unitPlacementVector.y), 0);
	unit->SetCurrentTile(mTileMap[unitPlacementVector.y][unitPlacementVector.x]);
	mTileMap[unitPlacementVector.y][unitPlacementVector.x]->SetInhabitant(unit);
	mUnitVector.push_back(unit);

	unitPlacementVector = GridVector(6, 19);
	unit = new WyvernRiderUnit(GridVector(unitPlacementVector.x, unitPlacementVector.y), 0);
	unit->SetCurrentTile(mTileMap[unitPlacementVector.y][unitPlacementVector.x]);
	mTileMap[unitPlacementVector.y][unitPlacementVector.x]->SetInhabitant(unit);
	mUnitVector.push_back(unit);

	unitPlacementVector = GridVector(0, 9);
	unit = new MageUnit(GridVector(unitPlacementVector.x, unitPlacementVector.y), 0);
	unit->SetCurrentTile(mTileMap[unitPlacementVector.y][unitPlacementVector.x]);
	mTileMap[unitPlacementVector.y][unitPlacementVector.x]->SetInhabitant(unit);
	mUnitVector.push_back(unit);

	unitPlacementVector = GridVector(8, 25);
	unit = new BonewalkerSwordUnit(GridVector(unitPlacementVector.x, unitPlacementVector.y), 1);
	unit->SetCurrentTile(mTileMap[unitPlacementVector.y][unitPlacementVector.x]);
	mTileMap[unitPlacementVector.y][unitPlacementVector.x]->SetInhabitant(unit);
	mUnitVector.push_back(unit);

	unitPlacementVector = GridVector(8, 26);
	unit = new BonewalkerSwordUnit(GridVector(unitPlacementVector.x, unitPlacementVector.y), 1);
	unit->SetCurrentTile(mTileMap[unitPlacementVector.y][unitPlacementVector.x]);
	mTileMap[unitPlacementVector.y][unitPlacementVector.x]->SetInhabitant(unit);
	mUnitVector.push_back(unit);

	unitPlacementVector = GridVector(8, 28);
	unit = new BonewalkerSwordUnit(GridVector(unitPlacementVector.x, unitPlacementVector.y), 1);
	unit->SetCurrentTile(mTileMap[unitPlacementVector.y][unitPlacementVector.x]);
	mTileMap[unitPlacementVector.y][unitPlacementVector.x]->SetInhabitant(unit);
	mUnitVector.push_back(unit);
}

Level::~Level()
{
	InternalClear();
}

void Level::Update(sf::Vector2f mouseWorldPos)
{
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Update(mouseWorldPos);

			Unit *inhabitant = t->GetInhabitant();
			GridVector gridVector = t->GetGridPosition();
			bool mouseover = t->GetMouseover(), click = false, rightClick = false;
			if (mouseover)
				mMouseoverPosition = gridVector;

			if (t->GetClicked())
			{
				click = true;
			}

			if (t->GetRightClicked())
			{
				rightClick = true;
			}

			if (inhabitant != nullptr)
			{
				inhabitant->SetMouseover(mouseover);
			}
			if (click)
			{
				mSelectedUnit = inhabitant;
				if (inhabitant != nullptr)
				{
					int moveRange = inhabitant->GetMovementRange();
					int y = gridVector.y - moveRange * 2;
					for (y; y <= gridVector.y + moveRange * 2; y++)
					{
						if (y < 0) y = 0;
						if (y >= mTileMap.size()) break;
						int x = gridVector.x - moveRange, max = gridVector.x + moveRange;
						if (max > mTileMap[0].size())
						{
							max = mTileMap[0].size();
							if (max < mTileMap[1].size()) max = mTileMap[1].size();
						}
						for (x; x < max; x++)
						{
							if (x < 0) x = 0;
							mTileMap[y][x]->SetHighlight(sf::Color(100, 100, 255, 127), true);
						}
					}
				}
			}
		}
	}
	if (mSelectedUnit != nullptr)
	{
		mSelectedUnit->SetMovingDown(true);
	}
	for each (Unit *u in mUnitVector)
	{
		u->Update(mouseWorldPos);
		u->SetMoving(false);
	}
}

void Level::Render(sf::RenderWindow *window)
{
	vector<Unit*> unitList;
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Render(window);
			Unit *inhabitant = t->GetInhabitant();
			if (inhabitant != nullptr)
				unitList.push_back(inhabitant);
		}
	}
	for each (Unit *u in unitList)
		u->Render(window);
}

GridVector Level::GetMouseoverPosition()
{
	return mMouseoverPosition;
}

Pathfinder* Level::GetPathfinder()
{
	return &mPathfinder;
}

void Level::InternalClear()
{
	while (!mTileMap.empty())
	{
		while (!mTileMap.back().empty())
		{
			delete mTileMap.back().back();
			assert(mTileMap.back().back() == nullptr);
			mTileMap.back().pop_back();
		}
		mTileMap.pop_back();
	}
	assert(mTileMap.empty());
	while (!mUnitVector.empty())
	{
		delete mUnitVector.back();
		assert(mUnitVector.back() == nullptr);
		mUnitVector.pop_back();
	}
}