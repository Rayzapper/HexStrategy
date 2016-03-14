#include "Boss.h"

Boss::Boss(Enemy *enemy)
	: mEnemy(enemy)
{

}

Boss::~Boss()
{
	delete mEnemy;
}

void Boss::Walk()
{
	mEnemy->Walk();
}

void Boss::Attack()
{
	mEnemy->Attack();
	AreaAttack();
}

Enemy* Boss::GetEnemy()
{
	return mEnemy;
}

void Boss::AreaAttack()
{
	cout << "Also hit the surrounding tiles!" << endl;
}