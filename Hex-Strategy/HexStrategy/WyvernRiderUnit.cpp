#include "WyvernRiderUnit.h"

WyvernRiderUnit::WyvernRiderUnit(GridVector gridVector, int team)
	: Unit(7, gridVector, team)
{
	mUnitTypes.push_back(INFANTRY);
	mUnitTypes.push_back(CAVALRY);
	mUnitTypes.push_back(FLIER);
	SetBaseMovement();
}

WyvernRiderUnit::~WyvernRiderUnit()
{

}