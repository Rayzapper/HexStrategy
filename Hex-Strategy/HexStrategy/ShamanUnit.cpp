#include "ShamanUnit.h"

ShamanUnit::ShamanUnit(GridVector gridVector, int team)
	: Unit(13, gridVector, team)
{
	mUnitClasses.push_back(INFANTRY);
	mUnitClasses.push_back(CASTER);
	SetBaseStats();
	mBaseHP = 7;
	mUnitHP = mBaseHP;
	mAttackDamage = 4;
}

ShamanUnit::~ShamanUnit()
{

}