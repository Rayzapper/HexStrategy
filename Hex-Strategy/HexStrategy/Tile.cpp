#include "Tile.h"

Tile::Tile(GridVector gridPosition)
	: mGridPosition(gridPosition)
{

}

void Tile::Update()
{

}

void Tile::Render()
{

}

void Tile::SetTileType(TileType type)
{
	mTileType = type;
}

GridVector Tile::GetGridPosition() const
{
	return mGridPosition;
}

TileType Tile::GetTileType() const
{
	return mTileType;
}
