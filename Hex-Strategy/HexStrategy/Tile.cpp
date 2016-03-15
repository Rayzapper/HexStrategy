#include "Tile.h"

const static int tileSize = 32;

Tile::Tile(int textureID, GridVector gridPosition, TileType tileType)
	: Entity(textureID),
	mGridPosition(gridPosition),
	mTileType(tileType)
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
