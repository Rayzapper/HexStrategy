#include "BonewalkerSwordUnit.h"

BonewalkerSwordUnit::BonewalkerSwordUnit(GridVector gridVector, int team)
	: Unit(8, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	SetBaseStats();
	mBaseHP = 10;
	mUnitHP = mBaseHP;
	mAttackDamage = 5;
}

BonewalkerSwordUnit::~BonewalkerSwordUnit()
{

}