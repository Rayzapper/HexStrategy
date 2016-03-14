#include "Tile.h"

Tile::Tile(int textureID, GridVector gridPosition)
	: Entity(textureID),
	mGridPosition(gridPosition)
{

}

Tile::~Tile()
{

}

void Tile::Update()
{

}

void Tile::Render(sf::RenderWindow *window)
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
