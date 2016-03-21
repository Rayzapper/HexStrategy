#include "MageUnit.h"

MageUnit::MageUnit(GridVector gridVector, int team)
	: Unit(6, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	mUnitClasses.push_back(CASTER);
	SetBaseStats();
	mBaseHP = 7;
	mUnitHP = mBaseHP;
	mAttackDamage = 4;
}

MageUnit::~MageUnit()
{

}