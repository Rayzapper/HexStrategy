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

	mPathfinder = Pathfinder();

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

	SpawnUnit(MERCENARY, GridVector(4, 8), 0);
	SpawnUnit(MAGE, GridVector(1, 13), 0);
	SpawnUnit(WYVERNRIDER, GridVector(15, 17), 0);
	SpawnUnit(BONEWALKERSWORD, GridVector(20, 18), 1);
	SpawnUnit(BONEWALKERSWORD, GridVector(21, 17), 1);
	SpawnUnit(BONEWALKERSWORD, GridVector(20, 20), 1);
	SpawnUnit(WYVERNRIDER, GridVector(12, 16), 1);
	SpawnUnit(MAGE, GridVector(11, 13), 0);
	SpawnUnit(BONEWALKERSWORD, GridVector(12, 2), 0);
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
				for (TileMap::size_type y = 0; y < mTileMap.size(); y++)
					for (TileRow::size_type x = 0; x < mTileMap[y].size(); x++)
						mTileMap[y][x]->SetHighlight(false);
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
						int x, max;
						x = floor((gridVector.x - moveRange) / 2);
						max = floor((gridVector.x + moveRange) / 2) + 1;
						if (max > mTileMap[y].size()) max = mTileMap[y].size();
						for (x; x < max; x++)
						{
							if (x < 0) x = 0;
							int tileDistance = mPathfinder.GetDistanceCost(mTileMap[y][x], t);
							if (tileDistance <= moveRange)
							{
								if (mPathfinder.IsTherePath(mTileMap[y][x], t))
									mTileMap[y][x]->SetHighlight(sf::Color(50, 50, 255, 127), true);
							}
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

	if (DebugManager::GetInstance().debugMode)
	{
		DebugManager::GetInstance().SetDebugString(DebugManager::GetInstance().GetDebugString() +
			"\nMouseover Tile GridX = " + to_string(mMouseoverPosition.x) +
			"\nMouseover Tile GridY = " + to_string(mMouseoverPosition.y));
		if (mSelectedUnit != nullptr)
		{
			DebugManager::GetInstance().SetDebugString(DebugManager::GetInstance().GetDebugString() +
				"\nSelected Unit GridX = " + to_string(mSelectedUnit->GetGridPosition().x) +
				"\nSelected Unit GridY = " + to_string(mSelectedUnit->GetGridPosition().y));
		}
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

void Level::SpawnUnit(UnitType type, GridVector position, int teamNr)
{
	assert(position.x % 2 == position.y % 2);
	Unit *unit;
	if (type == MERCENARY)
		unit = new MercenaryUnit(position, teamNr);
	/*else if (type == ARCHER)
		;*/
	else if (type == WYVERNRIDER)
		unit = new WyvernRiderUnit(position, teamNr);
	/*else if (type == CAVALLIER)
		;*/
	/*else if (type == FIGHTER)
		;*/
	else if (type == MAGE)
		unit = new MageUnit(position, teamNr);
	else if (type == BONEWALKERSWORD)
		unit = new BonewalkerSwordUnit(position, teamNr);
	/*else if (type == GARGOYLE)
		;*/
	else
		unit = new MercenaryUnit(position, teamNr);

	int x = floor(position.x / 2);
	Tile *tile = mTileMap[position.y][x];
	unit->SetCurrentTile(tile);
	tile->SetInhabitant(unit);
	mUnitVector.push_back(unit);
}