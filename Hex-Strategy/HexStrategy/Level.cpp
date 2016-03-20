#include "Level.h"
#include <cassert>
#include <iostream>
#include "MercenaryUnit.h"
#include "WyvernRiderUnit.h"
#include "MageUnit.h"
#include "BonewalkerSwordUnit.h"
#include "FighterUnit.h"
#include "GargoyleUnit.h"
#include "ArcherUnit.h"
#include "BonewalkerBowUnit.h"
#include "CavallierUnit.h"
#include "Button.h"

static const int tileSize = 32;

static sf::Color highlightBlue(100, 100, 255, 127), highlightRed(255, 100, 100, 127), highlightGreen(100, 255, 100, 127);

static sf::View uiView;
static vector<Button*> rightMenuButtons, unitMenuButtons;
static Button *cancelButton;
static sf::Font subMenuFont;

struct Selector
{
	GridVector gridPosition;
	sf::Vector2f renderPosition;
	sf::Texture *texture;
	sf::Sprite sprite;
	int animationOffset = 0;
	void Render(sf::RenderWindow *window)
	{
		sprite.setPosition(gridPosition.x * tileSize + 16, gridPosition.y * tileSize / 2 + 16);
		window->draw(sprite);
		sprite.rotate(90);
		window->draw(sprite);
		sprite.rotate(90);
		window->draw(sprite);
		sprite.rotate(90);
		window->draw(sprite);
		sprite.rotate(90);
	}
};

static Tile *selectedTile;
static Selector selector;
static sf::Texture selectorTexture;

Level::Level(GridVector mapSize, sf::RenderWindow *window)
	: mMapSize(mapSize)
{
	uiView = window->getView();

	if (!subMenuFont.loadFromFile("Resources/Fonts/Calibri.ttf"))
		cout << "Could not find font Calibri.ttf" << endl;

	if (!selectorTexture.loadFromFile("Resources/Graphics/Selector_sprite.png"))
		cout << "Could not find image Selector_sprite.png" << endl;
	selector.texture = &selectorTexture;
	selector.sprite.setTexture(*selector.texture);
	selector.sprite.setOrigin(tileSize / 2 + 4, tileSize / 2 + 4);

	Button *button = new Button(sf::IntRect(16, 16, 128, 32), "End Turn", &subMenuFont);
	button->SetCharSize(18);
	rightMenuButtons.push_back(button);
	button = new Button(sf::IntRect(16, 48, 128, 32), "Cancel", &subMenuFont);
	button->SetCharSize(18);
	rightMenuButtons.push_back(button);

	button = new Button(sf::IntRect(16, 16, 128, 32), "Wait", &subMenuFont);
	button->SetCharSize(18);
	unitMenuButtons.push_back(button);
	button = new Button(sf::IntRect(16, 48, 128, 32), "Attack", &subMenuFont);
	button->SetCharSize(18);
	unitMenuButtons.push_back(button);
	button = new Button(sf::IntRect(16, 80, 128, 32), "Cancel", &subMenuFont);
	button->SetCharSize(18);
	unitMenuButtons.push_back(button);

	cancelButton = new Button(sf::IntRect(16, 16, 128, 32), "Cancel", &subMenuFont);
	cancelButton->SetCharSize(18);

	for (int y = 0; y < mapSize.y; y++)
	{
		TileRow row;
		for (int x = 0; x < mapSize.x; x++)
		{
			TileType tileType = FLOOR;
			if (y <= 1 || x == 0 || y >= mapSize.y - 2 || x == mapSize.x - 1)
				tileType = WALL;
			else if (y % 8 == 4 && x % 4 == 2)
				tileType = HOLE;
			else if (x == 8 && (y > 18 || y < 16))
				tileType = WALL;
			if (y % 2 == 0 && x % 2 == 0)
			{
				row.push_back(new Tile(0, GridVector(x, y), tileType));
			}
			if (y % 2 == 1 && x % 2 == 1)
			{
				row.push_back(new Tile(0, GridVector(x, y), tileType));
			}
		}
		mTileMap.push_back(row);
	}

	mPathfinder = Pathfinder();

	int evenRowSize = mTileMap[0].size();
	int oddRowSize = mTileMap[1].size();
	int rowAmount = mTileMap.size();
	for (TileMap::size_type y = 0; y < mTileMap.size(); y++)
	{
		for (TileRow::size_type x = 0; x < mTileMap[y].size(); x++)
		{
			Tile *tile = mTileMap[y][x];
			if (y % 2 == 0)
			{
				if (x > 0 && y > 0)
					tile->SetNeighbor(mTileMap[y - 1][x - 1]);
				if (y > 0)
					tile->SetNeighbor(mTileMap[y - 2][x]);
				if (x <= oddRowSize - 1 && y > 0)
					tile->SetNeighbor(mTileMap[y - 1][x]);
				if (x > 0 && y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x - 1]);
				if (y < rowAmount - 2)
					tile->SetNeighbor(mTileMap[y + 2][x]);
				if (x <= oddRowSize - 1 && y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x]);
			}
			else
			{
				tile->SetNeighbor(mTileMap[y - 1][x]);
				if (y > 1)
					tile->SetNeighbor(mTileMap[y - 2][x]);
				if (x < evenRowSize - 1)
					tile->SetNeighbor(mTileMap[y - 1][x + 1]);
				if (y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x]);
				if (y < rowAmount - 2)
					tile->SetNeighbor(mTileMap[y + 2][x]);
				if (x < evenRowSize - 1 && y < rowAmount - 1)
					tile->SetNeighbor(mTileMap[y + 1][x + 1]);
			}
		}
	}

	SpawnUnit(MERCENARY, GridVector(4, 8), 0);
	SpawnUnit(MAGE, GridVector(1, 13), 0);
	SpawnUnit(WYVERNRIDER, GridVector(15, 17), 0);
	SpawnUnit(BONEWALKERSWORD, GridVector(20, 18), 1);
	SpawnUnit(BONEWALKERSWORD, GridVector(21, 17), 1);
	SpawnUnit(BONEWALKERSWORD, GridVector(20, 20), 1);
	SpawnUnit(BONEWALKERBOW, GridVector(21, 19), 1);
	SpawnUnit(WYVERNRIDER, GridVector(12, 16), 1);
	SpawnUnit(FIGHTER, GridVector(11, 13), 0);
	SpawnUnit(ARCHER, GridVector(12, 2), 0);
	SpawnUnit(CAVALLIER, GridVector(5, 21), 0);
}

Level::~Level()
{
	InternalClear();
}

void Level::Update(sf::Vector2f mouseWorldPos)
{
	if (mSubState == PLAY)
		PlayUpdate(mouseWorldPos);
	else if (mSubState == RIGHTMENU)
		RightMenuUpdate(mouseWorldPos);
	else if (mSubState == UNITMENU || mSubState == UNITATTACK)
		UnitMenuUpdate(mouseWorldPos);
	selector.gridPosition = mMouseoverPosition;

	if (DebugManager::GetInstance().debugMode)
	{
		DebugManager::GetInstance().SetDebugString(DebugManager::GetInstance().GetDebugString() +
			"\nMouseover Tile GridX = " + to_string(mMouseoverPosition.x) +
			"\nMouseover Tile GridY = " + to_string(mMouseoverPosition.y));
		if (mSelectedUnit != nullptr)
		{
			DebugManager::GetInstance().SetDebugString(DebugManager::GetInstance().GetDebugString() +
				"\nSelected Unit GridX = " + to_string(mSelectedUnit->GetGridPosition().x) +
				"\nSelected Unit GridY = " + to_string(mSelectedUnit->GetGridPosition().y));
		}
	}
}

void Level::Render(sf::RenderWindow *window)
{
	sf::View mainView = window->getView();
	vector<Unit*> unitList, movingList;
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Render(window);
			Unit *inhabitant = t->GetInhabitant();
			if (inhabitant != nullptr)
			{
				if (!inhabitant->GetMoving())
					unitList.push_back(inhabitant);
				else
					movingList.push_back(inhabitant);
			}
		}
	}
	for each (Unit *u in unitList)
		u->Render(window);
	for each (Unit *u in movingList)
		u->Render(window);
	window->setView(uiView);
	selector.Render(window);
	if (mSubState == RIGHTMENU)
		for each (Button *b in rightMenuButtons)
			b->Render(window);
	if (mSubState == UNITMENU)
		for each (Button *b in unitMenuButtons)
			b->Render(window);
	if (mSubState == UNITATTACK)
		cancelButton->Render(window);
	window->setView(mainView);
}

GridVector Level::GetMouseoverPosition()
{
	return mMouseoverPosition;
}

Pathfinder* Level::GetPathfinder()
{
	return &mPathfinder;
}

void Level::ChangeTurn()
{
	if (mPlayerTurn == 0) mPlayerTurn = 1;
	else if (mPlayerTurn == 1) mPlayerTurn = 0;
	for each (Unit *u in mUnitVector)
		u->SetMoveAvailable(true);
}

void Level::PlayUpdate(sf::Vector2f mouseWorldPos)
{
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Update(mouseWorldPos);

			Unit *inhabitant = t->GetInhabitant();
			GridVector gridVector = t->GetGridPosition();
			bool mouseover = t->GetMouseover(), click = false, rightClick = false;
			if (mouseover)
				mMouseoverPosition = gridVector;

			if (t->GetClicked())
				click = true;
			if (t->GetRightClicked() && !click)
				rightClick = true;

			if (inhabitant != nullptr && mSelectedUnit == nullptr && inhabitant->GetMoveAvailable())
				inhabitant->SetMouseover(mouseover);

			if (click)
			{
				if (!mUnitIsMoving)
				{
					for (TileMap::size_type y = 0; y < mTileMap.size(); y++)
						for (TileRow::size_type x = 0; x < mTileMap[y].size(); x++)
							mTileMap[y][x]->SetHighlight(false);

					if (find(mMovableTiles.begin(), mMovableTiles.end(), t) == mMovableTiles.end() || inhabitant != nullptr)
					{
						if (inhabitant != nullptr)
							if (inhabitant->GetMoveAvailable())
								mSelectedUnit = inhabitant;
						if (mSelectedUnit != nullptr)
							mSelectedUnit->SetMoving(false);
					}
					else
					{
						mUnitIsMoving = true;
						if (mSelectedUnit != nullptr)
						{
							mMovedUnit = mSelectedUnit;
							mMovedFromTile = mSelectedUnit->GetCurrentTile();
							mSelectedUnit->UnitMove(mPathfinder.FindPath(mSelectedUnit->GetCurrentTile(), t));
							AssignUnitTile(t, mSelectedUnit);
							mSelectedUnit = nullptr;
							mSubState = UNITMENU;
						}
					}

					if (inhabitant != nullptr)
					{
						mSelectedUnit->SetMouseover(false);
						mMovableTiles = mPathfinder.GetMovableTiles(t, inhabitant);
						for each (Tile *t in mMovableTiles)
							t->SetHighlight(sf::Color(50, 50, 255, 127), true);
					}
				}
			}
			else if (rightClick)
			{
				if (!mUnitIsMoving)
				{
					for (TileMap::size_type y = 0; y < mTileMap.size(); y++)
						for (TileRow::size_type x = 0; x < mTileMap[y].size(); x++)
							mTileMap[y][x]->SetHighlight(false);
					mSelectedUnit = nullptr;
					mSubState = RIGHTMENU;
				}
			}
		}
	}

	if (mSelectedUnit != nullptr)
	{
		mSelectedUnit->SetMovingDown(true);
	}
	mUnitIsMoving = false;
	for each (Unit *u in mUnitVector)
	{
		u->Update(mouseWorldPos);
		if (u->GetMoving())
			mUnitIsMoving = true;
	}
}

void Level::RightMenuUpdate(sf::Vector2f mouseWorldPos)
{
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Update(mouseWorldPos);

			GridVector gridVector = t->GetGridPosition();
			bool mouseover = t->GetMouseover();
			if (mouseover)
				mMouseoverPosition = gridVector;
		}
	}
	for each (Unit *u in mUnitVector)
	{
		u->Update(mouseWorldPos);
	}
	for each (Button *b in rightMenuButtons)
	{
		b->Update(mouseWorldPos);

		if (b->GetClicked())
		{
			string text = b->GetButtonString();

			if (text == "Cancel")
				mSubState = PLAY;
		}
	}
}

void Level::UnitMenuUpdate(sf::Vector2f mouseWorldPos)
{
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Update(mouseWorldPos);

			GridVector gridVector = t->GetGridPosition();
			bool mouseover = t->GetMouseover();
			if (mouseover)
				mMouseoverPosition = gridVector;
		}
	}
	mUnitIsMoving = false;
	for each (Unit *u in mUnitVector)
	{
		u->Update(mouseWorldPos);
		if (u->GetMoving())
			mUnitIsMoving = true;
	}
	if (!mUnitIsMoving)
	{
		if (mSubState == UNITMENU)
		{
			for each (Button *b in unitMenuButtons)
			{
				b->Update(mouseWorldPos);

				if (b->GetClicked())
				{
					string text = b->GetButtonString();

					if (text == "Wait")
					{
						mSubState = PLAY;
						mMovedUnit->SetMoveAvailable(false);
					}
					if (text == "Attack")
					{
						mSubState = UNITATTACK;
						int minRange = mMovedUnit->GetMinAttackRange(), maxRange = mMovedUnit->GetMaxAttackRange();
						for (int i = minRange; i < maxRange + 1; i++)
							for each (Tile *t in mPathfinder.GetTileCircle(mMovedUnit->GetCurrentTile(), i))
							{
								mAttackableTiles.push_back(t);
								t->SetHighlight(sf::Color(255, 50, 50, 127), true);
							}
					}
					if (text == "Cancel")
					{
						mSubState = PLAY;
						AssignUnitTile(mMovedFromTile, mMovedUnit);
						GridVector gridVector = mMovedFromTile->GetGridPosition();
						sf::Vector2f vector2f(gridVector.x * tileSize, gridVector.y * tileSize / 2);
						mMovedUnit->SetCurrentPosition(vector2f);
					}
				}
			}
		}
		else if (mSubState == UNITATTACK)
		{
			cancelButton->Update(mouseWorldPos);
			for (TileMap::size_type y = 0; y < mTileMap.size(); y++)
				for (TileRow::size_type x = 0; x < mTileMap[y].size(); x++)
					mTileMap[y][x]->SetHighlight(false);

			if (cancelButton->GetClicked())
			{
				mSubState = UNITMENU;
				mAttackableTiles.clear();
			}
			else
			{
				for each (Tile *t in mAttackableTiles)
				{
					t->SetHighlight(sf::Color(255, 50, 50, 127), true);
					bool click = t->GetClicked();
				}
			}
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
	while (!mUnitVector.empty())
	{
		delete mUnitVector.back();
		assert(mUnitVector.back() == nullptr);
		mUnitVector.pop_back();
	}
	assert(mUnitVector.empty());
	while (!rightMenuButtons.empty())
	{
		delete rightMenuButtons.back();
		assert(rightMenuButtons.back() == nullptr);
		rightMenuButtons.pop_back();
	}
	assert(rightMenuButtons.empty());
	while (!unitMenuButtons.empty())
	{
		delete unitMenuButtons.back();
		assert(unitMenuButtons.back() == nullptr);
		unitMenuButtons.pop_back();
	}
	assert(unitMenuButtons.empty());
}

void Level::SpawnUnit(UnitType type, GridVector position, int teamNr)
{
	assert(position.x % 2 == position.y % 2);
	int x = floor(position.x / 2);
	Tile *tile = mTileMap[position.y][x];
	assert(tile->GetInhabitant() == nullptr);
	Unit *unit;
	if (type == MERCENARY)
		unit = new MercenaryUnit(position, teamNr);
	else if (type == FIGHTER)
		unit = new FighterUnit(position, teamNr);
	else if (type == ARCHER)
		unit = new ArcherUnit(position, teamNr);
	else if (type == WYVERNRIDER)
		unit = new WyvernRiderUnit(position, teamNr);
	else if (type == CAVALLIER)
		unit = new CavallierUnit(position, teamNr);
	else if (type == MAGE)
		unit = new MageUnit(position, teamNr);
	else if (type == BONEWALKERSWORD)
		unit = new BonewalkerSwordUnit(position, teamNr);
	else if (type == BONEWALKERBOW)
		unit = new BonewalkerBowUnit(position, teamNr);
	else if (type == GARGOYLE)
		unit = new GargoyleUnit(position, teamNr);
	else
		unit = new MercenaryUnit(position, teamNr);

	unit->SetCurrentTile(tile);
	tile->SetInhabitant(unit);
	mUnitVector.push_back(unit);
}

void Level::AssignUnitTile(Tile *newTile, Unit *unit)
{
	unit->GetCurrentTile()->SetInhabitant(nullptr);
	newTile->SetInhabitant(unit);
	unit->SetCurrentTile(newTile);
}