#include "MageUnit.h"

MageUnit::MageUnit(GridVector gridVector, int team)
	: Unit(6, gridVector, team)
{
	mUnitTypes.push_back(INFANTRY);
	mUnitTypes.push_back(MAGE);
	SetBaseMovement();
}

MageUnit::~MageUnit()
{

}