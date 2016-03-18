#include "Tile.h"
#include "Button.h"
#include <cassert>

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

	mTileHighlight.setSize(sf::Vector2f(tileSize, tileSize));
	mTileHighlight.setPosition(mRenderPosition);
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
	if (mHighlighted)
		window->draw(mTileHighlight);
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
	assert(neighbor != nullptr);
	mNeighbors.push_back(neighbor);
}

void Tile::SetInhabitant(Unit *unit)
{
	mInhabitant = unit;
}

void Tile::SetPathParent(Tile *tile)
{
	mPathParent = tile;
}

void Tile::SetPathValues(int gCost, int hCost)
{
	mPathValues.gCost = gCost;
	mPathValues.hCost = hCost;
	mPathValues.fCost = gCost + hCost;
}

void Tile::SetHighlight(sf::Color color, bool highlight)
{
	mTileHighlight.setFillColor(color);
	mHighlighted = highlight;
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

Unit* Tile::GetInhabitant() const
{
	return mInhabitant;
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

Tile* Tile::GetPathParent() const
{
	return mPathParent;
}

PathValues Tile::GetPathValues()
{
	return mPathValues;
}

vector<Tile*> Tile::GetPath(vector<Tile*> path)
{
	if (mPathParent != nullptr)
	{
		path = mPathParent->GetPath(path);
		path.push_back(mPathParent);
	}
	return path;
}