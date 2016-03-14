#include "Level.h"

Level::Level()
{

}

Level::~Level()
{
	InternalClear();
}

void Level::Update()
{

}

void Level::Render()
{

}

void Level::InternalClear()
{
	while (!mTileMap.empty())
	{
		while (!mTileMap.back().empty())
		{

		}
	}
}