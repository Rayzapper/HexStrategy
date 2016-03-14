#include "Level.h"
#include <cassert>

Level::Level(GridVector mapSize)
	: mMapSize(mapSize)
{

}

Level::~Level()
{
	InternalClear();
}

void Level::Update()
{

}

void Level::Render(sf::RenderWindow *window)
{

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