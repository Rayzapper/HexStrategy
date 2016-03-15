#include "Level.h"
#include <cassert>

Level::Level(GridVector mapSize)
	: mMapSize(mapSize)
{
	for (int x = 0; x < mapSize.GetX(); x++)
	{
		TileRow collumn;
		for (int y = 0; y < mapSize.GetY(); y++)
		{
			Tile *tile = new Tile(0, GridVector(x, y), FLOOR);
			collumn.push_back(tile);
		}
		mTileMap.push_back(collumn);
	}
}

Level::~Level()
{
	InternalClear();
}

void Level::Update()
{
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Update();
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