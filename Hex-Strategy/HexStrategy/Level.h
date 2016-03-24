#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Pathfinder.h"

#include "DebugManager.h"

enum SubState
{
	PLAY,
	RIGHTMENU,
	UNITMENU,
	TARGETING,
	UNITATTACK,
	TURNCHANGE,
	WIN,
	LEVELOVER
};

enum UnitType
{
	MERCENARY,
	FIGHTER,
	ARCHER,
	CAVALLIER,
	WYVERNRIDER,
	MAGE,
	BONEWALKERSWORD,
	BONEWALKERBOW,
	GARGOYLE,
	TARVOS,
	SHAMAN,
	REVENANT
};

class Level
{
public:
	Level(GridVector mapSize, sf::RenderWindow *window);
	~Level();
	typedef vector<Tile*> TileRow;
	typedef vector<TileRow> TileMap;
	typedef vector<Unit*> UnitVector;
	void Update(sf::Vector2f mouseWorldPos);
	void Render(sf::RenderWindow *window);
	GridVector GetMouseoverPosition();
	Pathfinder* GetPathfinder();
	SubState GetSubState() const;
	void ChangeTurn();
	void PlayUpdate(sf::Vector2f mouseWorldPos);
	void RightMenuUpdate(sf::Vector2f mouseWorldPos);
	void UnitMenuUpdate(sf::Vector2f mouseWorldPos);
	void TurnChangeUpdate(sf::Vector2f mouseWorldPos);
	void AttackUpdate(sf::Vector2f mouseWorldPos);
	void WinUpdate(sf::Vector2f mouseWorldPos);
private:
	void InternalClear();
	void SpawnUnit(UnitType type, GridVector position, int teamNr);
	void AssignUnitTile(Tile *newTile, Unit *unit);
	void UnitAttack(Unit *attacker, Unit *defender);
	TileMap mTileMap;
	GridVector mMapSize, mMouseoverPosition;
	UnitVector mUnitVector;
	Unit *mSelectedUnit, *mMovedUnit, *mAttacker, *mDefender;
	Pathfinder mPathfinder;
	vector<Tile*> mMovableTiles, mAttackableTiles;
	bool mUnitIsMoving = false, mUnitIsAttacking = false, mRetaliate = false;
	int mPlayerTurn = 0;
	SubState mSubState = PLAY;
	Tile *mMovedFromTile;
	sf::Clock mTurnChangeClock;
};

#endif