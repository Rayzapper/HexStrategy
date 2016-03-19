#include "WyvernRiderUnit.h"

WyvernRiderUnit::WyvernRiderUnit(GridVector gridVector, int team)
	: Unit(7, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	mUnitClasses.push_back(CAVALRY);
	mUnitClasses.push_back(FLIER);
	SetBaseStats();
}

WyvernRiderUnit::~WyvernRiderUnit()
{

}