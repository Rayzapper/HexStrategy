#include "MageUnit.h"

MageUnit::MageUnit(GridVector gridVector, int team)
	: Unit(6, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	mUnitClasses.push_back(CASTER);
	SetBaseMovement();
}

MageUnit::~MageUnit()
{

}