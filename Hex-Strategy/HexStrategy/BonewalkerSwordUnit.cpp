#include "BonewalkerSwordUnit.h"

BonewalkerSwordUnit::BonewalkerSwordUnit(GridVector gridVector, int team)
	: Unit(8, gridVector, team)
{
	mUnitTypes.push_back(INFANTRY);
	SetBaseMovement();
}

BonewalkerSwordUnit::~BonewalkerSwordUnit()
{

}