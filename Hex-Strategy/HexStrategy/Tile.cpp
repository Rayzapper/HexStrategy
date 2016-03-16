#include "Tile.h"

const static int tileSize = 32;

Tile::Tile(int textureID, GridVector gridPosition, TileType tileType)
	: Entity(textureID),
	mGridPosition(gridPosition),
	mTileType(tileType)
{
	mRenderPosition.x = gridPosition.GetX() * tileSize;
	mRenderPosition.y = gridPosition.GetY() * tileSize / 2;
	mSprite.setPosition(mRenderPosition);
	if (mTileType == FLOOR)
		mSprite.setTextureRect(sf::IntRect(tileSize, 0, tileSize, tileSize));
	else if (mTileType == WALL)
		mSprite.setTextureRect(sf::IntRect(tileSize * 2, 0, tileSize, tileSize));
	else if (mTileType == HOLE)
		mSprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));

	mHitBox.height = tileSize;
	mHitBox.width = tileSize;
	mHitBox.left = mRenderPosition.x;
	mHitBox.top = mRenderPosition.y;
}

Tile::~Tile()
{

}

void Tile::UpdateMouse(sf::Vector2i mouseWorldPos)
{
	mMouseWorldPosition = mouseWorldPos;
}

void Tile::Update()
{
	
}

void Tile::Render(sf::RenderWindow *window)
{
	window->draw(mSprite);
}

void Tile::SetTileType(TileType type)
{
	mTileType = type;
}

void Tile::SetTerrainType(TerrainType type)
{
	mTerrainType = type;
}

void Tile::SetNeighbor(Tile *neighbor)
{
	mNeighbors.push_back(neighbor);
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

std::vector<Tile*> Tile::GetNeighbors() const
{
	return mNeighbors;
}

bool Tile::GetMouseover() const
{
	return mHitBox.contains(mMouseWorldPosition);
}