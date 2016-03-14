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

void Tile::SetTerrainType(TerrainType type)
{
	mTerrainType = type;
}

GridVector Tile::GetGridPosition() const
{
	return mGridPosition;
}

TileType Tile::GetTileType() const
{
	return mTileType;
}

TerrainType Tile::GetTerrainType() const
{
	return mTerrainType;
}
