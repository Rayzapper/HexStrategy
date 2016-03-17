#include "Tile.h"
#include "Button.h"

const static int tileSize = 32;

Tile::Tile(int textureID, GridVector gridPosition, TileType tileType)
	: Entity(textureID),
	mGridPosition(gridPosition),
	mTileType(tileType)
{
	mRenderPosition.x = gridPosition.x * tileSize;
	mRenderPosition.y = gridPosition.y * tileSize / 2;
	mSprite.setPosition(mRenderPosition);
	if (mTileType == FLOOR)
		mSprite.setTextureRect(sf::IntRect(tileSize, 0, tileSize, tileSize));
	else if (mTileType == WALL)
		mSprite.setTextureRect(sf::IntRect(tileSize * 2, 0, tileSize, tileSize));
	else if (mTileType == HOLE)
		mSprite.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));

	mButton = new Button(sf::IntRect(mRenderPosition.x, mRenderPosition.y, tileSize, tileSize));
}

Tile::~Tile()
{
	delete mButton;
}

void Tile::Update(sf::Vector2f mouseWorldPos)
{
	mMouseWorldPosition = sf::Vector2i(mouseWorldPos);
	mButton->Update(mouseWorldPos);
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

bool Tile::GetMouseover()
{
	return mButton->GetMouseover();
}

bool Tile::GetClicked()
{
	return mButton->GetClicked();
}

bool Tile::GetRightClicked()
{
	return mButton->GetRightClicked();
}
