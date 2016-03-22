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
#include "TarvosUnit.h"
#include "RevenantUnit.h"
#include "ShamanUnit.h"
#include "Button.h"

static const int tileSize = 32;

static sf::Color highlightBlue(100, 100, 255, 127), highlightRed(255, 100, 100, 127), highlightGreen(100, 255, 100, 127);

static sf::View uiView;
static vector<Button*> rightMenuButtons, unitMenuButtons;
static Button *cancelButton;
static sf::Font subMenuFont;
static bool displayHP = false;

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

static sf::Text turnText, hpText;
static float turnTextBaseX;

Level::Level(GridVector mapSize, sf::RenderWindow *window)
	: mMapSize(mapSize)
{
	uiView = window->getView();

	if (!subMenuFont.loadFromFile("Resources/Fonts/Calibri.ttf"))
		cout << "Could not find font Calibri.ttf" << endl;

	turnText.setFont(subMenuFont);
	turnText.setCharacterSize(100);
	turnTextBaseX = window->getSize().x + 10;
	turnText.setPosition(sf::Vector2f(turnTextBaseX, window->getSize().y / 2 - 50));

	hpText.setFont(subMenuFont);
	hpText.setCharacterSize(24);
	hpText.setColor(sf::Color::Black);

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

	button = new Button(sf::IntRect(0, 0, 128, 32), "Wait", &subMenuFont);
	button->SetCharSize(18);
	button->SetColor(sf::Color(50, 50, 200, 191));
	unitMenuButtons.push_back(button);
	button = new Button(sf::IntRect(0, 0, 128, 32), "Attack", &subMenuFont);
	button->SetCharSize(18);
	button->SetColor(sf::Color(50, 50, 200, 191));
	unitMenuButtons.push_back(button);
	button = new Button(sf::IntRect(0, 0, 128, 32), "Cancel", &subMenuFont);
	button->SetCharSize(18);
	button->SetColor(sf::Color(50, 50, 200, 191));
	unitMenuButtons.push_back(button);

	cancelButton = new Button(sf::IntRect(0, 0, 128, 32), "Cancel", &subMenuFont);
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
	SpawnUnit(REVENANT, GridVector(20, 18), 1);
	SpawnUnit(BONEWALKERSWORD, GridVector(21, 17), 1);
	SpawnUnit(SHAMAN, GridVector(20, 20), 1);
	SpawnUnit(BONEWALKERBOW, GridVector(21, 19), 1);
	SpawnUnit(GARGOYLE, GridVector(12, 16), 1);
	SpawnUnit(FIGHTER, GridVector(11, 13), 0);
	SpawnUnit(ARCHER, GridVector(12, 2), 0);
	SpawnUnit(CAVALLIER, GridVector(5, 21), 0);
	SpawnUnit(TARVOS, GridVector(22, 26), 1);
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
	else if (mSubState == UNITMENU || mSubState == TARGETING)
		UnitMenuUpdate(mouseWorldPos);
	else if (mSubState == TURNCHANGE)
		TurnChangeUpdate(mouseWorldPos);
	else if (mSubState == UNITATTACK)
		AttackUpdate(mouseWorldPos);
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
				if (inhabitant->GetHp() > 0)
				{
					if (!inhabitant->GetMoving())
						unitList.push_back(inhabitant);
					else
						movingList.push_back(inhabitant);
				}
			}
		}
	}
	for each (Unit *u in unitList)
		u->Render(window);
	for each (Unit *u in movingList)
		u->Render(window);
	if (mSubState == PLAY && displayHP)
		window->draw(hpText);
	window->setView(uiView);
	selector.Render(window);
	if (mSubState == RIGHTMENU)
		for each (Button *b in rightMenuButtons)
			b->Render(window);
	if (mSubState == UNITMENU)
		for each (Button *b in unitMenuButtons)
			b->Render(window);
	if (mSubState == TARGETING)
		cancelButton->Render(window);
	if (mSubState == TURNCHANGE)
		window->draw(turnText);
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

SubState Level::GetSubState() const
{
	return mSubState;
}

void Level::ChangeTurn()
{
	mTurnChangeClock.restart();
	if (mPlayerTurn == 0) mPlayerTurn = 1;
	else if (mPlayerTurn == 1) mPlayerTurn = 0;
	for each (Unit *u in mUnitVector)
		u->SetMoveAvailable(true);
	if (mPlayerTurn == 0)
	{
		turnText.setString("Player 1 Turn");
		turnText.setColor(sf::Color::Blue);
	}
	else if (mPlayerTurn == 1)
	{
		turnText.setString("Player 2 Turn");
		turnText.setColor(sf::Color::Red);
	}
}

void Level::PlayUpdate(sf::Vector2f mouseWorldPos)
{
	displayHP = false;
	for each (TileRow r in mTileMap)
	{
		for each (Tile *t in r)
		{
			t->Update(mouseWorldPos);

			Unit *inhabitant = t->GetInhabitant();
			if (inhabitant != 0)
				if (inhabitant->GetHp() <= 0)
				{
					t->SetInhabitant(0);
					inhabitant = 0;
				}
			GridVector gridVector = t->GetGridPosition();
			bool mouseover = t->GetMouseover(), click = false, rightClick = false;
			if (mouseover)
				mMouseoverPosition = gridVector;

			if (t->GetClicked())
				click = true;
			if (t->GetRightClicked() && !click)
				rightClick = true;

			if (inhabitant != 0 && mouseover)
			{
				displayHP = true;
				hpText.setString(to_string(inhabitant->GetHp()) + "/" + to_string(inhabitant->GetBaseHp()));
				hpText.setPosition(t->GetGridPosition().x * tileSize, t->GetGridPosition().y * tileSize / 2 + tileSize);
			}

			if (inhabitant != nullptr && mSelectedUnit == nullptr && inhabitant->GetMoveAvailable() && inhabitant->GetTeam() == mPlayerTurn)
				inhabitant->SetMouseover(mouseover);

			if (click)
			{
				if (!mUnitIsMoving)
				{
					for (TileMap::size_type y = 0; y < mTileMap.size(); y++)
						for (TileRow::size_type x = 0; x < mTileMap[y].size(); x++)
							mTileMap[y][x]->SetHighlight(false);

					if (find(mMovableTiles.begin(), mMovableTiles.end(), t) == mMovableTiles.end() || (inhabitant != nullptr && inhabitant != mSelectedUnit))
					{
						if (inhabitant != nullptr)
						{
							if (inhabitant->GetMoveAvailable() && inhabitant->GetTeam() == mPlayerTurn)
								mSelectedUnit = inhabitant;
							else if (mSelectedUnit != inhabitant)
								mSelectedUnit = nullptr;
						}
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
							sf::Vector2f buttonPosition;

							if (mouseWorldPos.x < uiView.getSize().x - 150) 
								buttonPosition.x = t->GetGridPosition().x * tileSize + tileSize * 1.5;
							else
								buttonPosition.x = t->GetGridPosition().x * tileSize - 100 - tileSize * 1.5;

							if (mouseWorldPos.y < uiView.getSize().y - 150)
								buttonPosition.y = t->GetGridPosition().y * tileSize / 2;
							else
								buttonPosition.y = t->GetGridPosition().y * tileSize / 2 - 150;

							for (vector<Button*>::size_type i = 0; i < unitMenuButtons.size(); i++)
							{
								unitMenuButtons[i]->SetPosition(sf::Vector2f(buttonPosition.x, buttonPosition.y + i * 32));
							}
							mSubState = UNITMENU;
						}
					}

					if (inhabitant != nullptr && mSelectedUnit != nullptr)
					{
						if (inhabitant->GetMoveAvailable() && inhabitant->GetTeam() == mPlayerTurn)
						{
							mSelectedUnit->SetMouseover(false);
							mMovableTiles = mPathfinder.GetMovableTiles(t, inhabitant);
							for each (Tile *t in mMovableTiles)
								t->SetHighlight(sf::Color(50, 50, 255, 127), true);
						}
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
	bool endTurn = true;
	for each (Unit *u in mUnitVector)
	{
		u->Update(mouseWorldPos);
		if (u->GetMoving())
			mUnitIsMoving = true;
		if (u->GetMoveAvailable() && u->GetTeam() == mPlayerTurn)
			endTurn = false;
	}
	bool player1Win = true, player2Win = true;
	for (vector<Unit*>::size_type i = 0; i < mUnitVector.size(); i++)
	{
		if (mUnitVector[i]->GetSubState() == DEAD)
		{
			delete mUnitVector[i];
			mUnitVector.erase(mUnitVector.begin() + i);
			i--;
		}
		else
		{
			if (mUnitVector[i]->GetTeam() == 0) player2Win = false;
			else if (mUnitVector[i]->GetTeam() == 1) player1Win = false;
		}
	}
	if (player1Win || player2Win)
		mSubState = WIN;
	if (endTurn && mSubState != WIN)
	{
		mSubState = TURNCHANGE;
		ChangeTurn();
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

			if (text == "End Turn")
			{
				mSubState = TURNCHANGE;
				ChangeTurn();
			}
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
						mSubState = TARGETING;
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
		else if (mSubState == TARGETING)
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

					if (click)
					{
						Unit *inhabitant = t->GetInhabitant();
						if (inhabitant != nullptr)
						{
							mSubState = UNITATTACK;
							mUnitIsAttacking = true;
							UnitAttack(mMovedUnit, inhabitant);
							for each (Tile *t in mAttackableTiles)
								t->SetHighlight(false);
							break;
						}
					}
				}
			}
		}
	}
}

void Level::TurnChangeUpdate(sf::Vector2f mouseWorldPos)
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

	turnText.setPosition(turnText.getPosition().x - 8, turnText.getPosition().y);

	if (mTurnChangeClock.getElapsedTime().asSeconds() >= 3)
	{
		mSubState = PLAY;
		turnText.setPosition(turnTextBaseX, turnText.getPosition().y);
	}
}

enum AttackState
{
	CHARGE,
	RETREAT
};

static sf::Clock attackClock;
static sf::Vector2f attackAngle;
static AttackState attackState = CHARGE;
static const int attackMoveSpeed = 4;

void Level::AttackUpdate(sf::Vector2f mouseWorldPos)
{
	for each (Unit *u in mUnitVector)
		if (u != mAttacker && u != mDefender)
			u->Update(mouseWorldPos);
	if (attackState == CHARGE)
	{
		sf::Vector2f newPos = mAttacker->GetCurrentPosition();
		newPos.x = newPos.x + attackAngle.x * attackMoveSpeed;
		newPos.y = newPos.y + attackAngle.y * attackMoveSpeed;
		mAttacker->SetCurrentPosition(newPos);
		if (attackClock.getElapsedTime().asMilliseconds() >= 100)
		{
			attackState = RETREAT;
			attackClock.restart();
			mDefender->ChangeHP(-mAttacker->GetAttackDamage());
		}
	}
	else if (attackState == RETREAT)
	{
		sf::Vector2f newPos = mAttacker->GetCurrentPosition();
		newPos.x = newPos.x - attackAngle.x * attackMoveSpeed;
		newPos.y = newPos.y - attackAngle.y * attackMoveSpeed;
		mAttacker->SetCurrentPosition(newPos);
		if (attackClock.getElapsedTime().asMilliseconds() >= 100)
		{
			attackState = CHARGE;
			mAttacker->SetCurrentPosition(sf::Vector2f(mAttacker->GetCurrentTile()->GetGridPosition().x * tileSize, mAttacker->GetCurrentTile()->GetGridPosition().y * tileSize / 2));
			attackClock.restart();
			if (!mRetaliate)
				mSubState = PLAY;
			if (mRetaliate && mDefender->GetHp() > 0)
			{
				mRetaliate = false;
				Unit *temp = mAttacker;
				mAttacker = mDefender;
				mDefender = temp;
				attackAngle.x *= -1;
				attackAngle.y *= -1;
			}
			else
			{
				mRetaliate = false;
				mSubState = PLAY;
			}
		}
	}
	if (mAttacker != 0)
		mAttacker->Update(mouseWorldPos);
	if (mDefender != 0)
		mDefender->Update(mouseWorldPos);
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
	else if (type == TARVOS)
		unit = new TarvosUnit(position, teamNr);
	else if (type == REVENANT)
		unit = new RevenantUnit(position, teamNr);
	else if (type == SHAMAN)
		unit = new ShamanUnit(position, teamNr);
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

void Level::UnitAttack(Unit *attacker, Unit *defender)
{
	int range = mPathfinder.GetDistanceCost(attacker->GetCurrentTile(), defender->GetCurrentTile());
	bool retaliate = false;
	if (defender->GetMinAttackRange() <= range && range <= defender->GetMaxAttackRange())
		retaliate = true;
	mAttacker = attacker;
	mDefender = defender;
	mRetaliate = retaliate;
	attackAngle = defender->GetCurrentPosition() - attacker->GetCurrentPosition();
	attackAngle = attackAngle / hypotf(attackAngle.x, attackAngle.y);
	for each (Tile *t in mAttackableTiles)
		t->SetHighlight(false);
	mAttackableTiles.clear();
	mAttacker->SetMoveAvailable(false);
	attackClock.restart();
}