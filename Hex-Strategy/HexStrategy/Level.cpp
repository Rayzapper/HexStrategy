#include "Level.h"
#include <cassert>

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
		}
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
}