#include "Level.h"
#include <cassert>
#include <iostream>
#include "MercenaryUnit.h"
#include "WyvernRiderUnit.h"
#include "MageUnit.h"
#include "BonewalkerSwordUnit.h"

Level::Level(GridVector mapSize)
	: mMapSize(mapSize)
{
	for (int x = 0; x < mapSize.x; x++)
	{
		TileRow collumn;
		for (int y = 0; y < mapSize.y; y++)
		{
			TileType tileType = FLOOR;
			if (y == 0 || x == 0 || y == mapSize.y - 1 || x == mapSize.x - 1)
				tileType = WALL;
			else if (y % 4 == 2 && x % 4 == 2)
				tileType = HOLE;
			else if (x == 8 && (y > 9 || y < 8))
				tileType = WALL;
			Tile *tile = new Tile(0, GridVector(x, y * 2 + (x % 2)), tileType);
			collumn.push_back(tile);
		}
		mTileMap.push_back(collumn);
	}

	for (TileMap::size_type x = 0; x < mTileMap.size(); x++)
	{
		for (TileRow::size_type y = 0; y < mTileMap[x].size(); y++)
		{
			if (x % 2 == 0)
			{
				if (y > 0)
				{
					if (x > 0)
						mTileMap[x][y]->SetNeighbor(mTileMap[x - 1][y - 1]);
					mTileMap[x][y]->SetNeighbor(mTileMap[x][y - 1]);
					if (x < mTileMap.size() - 1)
						mTileMap[x][y]->SetNeighbor(mTileMap[x + 1][y - 1]);
				}
				if (x > 0)
					mTileMap[x][y]->SetNeighbor(mTileMap[x - 1][y]);
				if (y < mTileMap[x].size() - 1)
					mTileMap[x][y]->SetNeighbor(mTileMap[x][y + 1]);
				if (x < mTileMap.size() - 1)
					mTileMap[x][y]->SetNeighbor(mTileMap[x + 1][y]);
			}
			else
			{
				if (x > 0)
					mTileMap[x][y]->SetNeighbor(mTileMap[x - 1][y]);
				if (y > 0)
					mTileMap[x][y]->SetNeighbor(mTileMap[x][y - 1]);
				if (x < mTileMap.size() - 1)
					mTileMap[x][y]->SetNeighbor(mTileMap[x + 1][y]);
				if (y < mTileMap[x].size() - 1)
				{
					if (x > 0)
						mTileMap[x][y]->SetNeighbor(mTileMap[x - 1][y + 1]);
					mTileMap[x][y]->SetNeighbor(mTileMap[x][y + 1]);
					if (x < mTileMap.size() - 1)
						mTileMap[x][y]->SetNeighbor(mTileMap[x + 1][y + 1]);
				}
			}
		}
	}

	MercenaryUnit *merc = new MercenaryUnit(GridVector(4, 8), 0);
	merc->SetCurrentTile(mTileMap[4][4]);
	mUnitVector.push_back(merc);

	WyvernRiderUnit *wyvern = new WyvernRiderUnit(GridVector(15, 17), 0);
	wyvern->SetCurrentTile(mTileMap[15][8]);
	mUnitVector.push_back(wyvern);

	MageUnit *mage = new MageUnit(GridVector(1, 7), 0);
	mage->SetCurrentTile(mTileMap[1][3]);
	mUnitVector.push_back(mage);

	BonewalkerSwordUnit *skel1 = new BonewalkerSwordUnit(GridVector(19, 19), 0);
	skel1->SetCurrentTile(mTileMap[19][9]);
	mUnitVector.push_back(skel1);

	BonewalkerSwordUnit *skel2 = new BonewalkerSwordUnit(GridVector(20, 18), 0);
	skel2->SetCurrentTile(mTileMap[20][9]);
	mUnitVector.push_back(skel2);

	BonewalkerSwordUnit *skel3 = new BonewalkerSwordUnit(GridVector(19, 21), 0);
	skel3->SetCurrentTile(mTileMap[19][10]);
	mUnitVector.push_back(skel3);

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
			if (t->GetMouseover())
				mMouseoverPosition = t->GetGridPosition();
			GridVector gridVector = t->GetGridPosition();
			if (t->GetClicked())
			{
				
			}
			if (t->GetRightClicked())
			{
				
			}
		}
	}
	for each (Unit *u in mUnitVector)
	{
		u->Update(mouseWorldPos);
	}
}

void Level::Render(sf::RenderWindow *window)
{
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Render(window);
		}
	}
	for each (Unit *u in mUnitVector)
	{
		u->Render(window);
	}
}

GridVector Level::GetMouseoverPosition()
{
	return mMouseoverPosition;
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