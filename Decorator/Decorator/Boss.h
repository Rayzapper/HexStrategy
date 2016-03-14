#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss(Enemy *enemy);
	virtual ~Boss();
	virtual void Walk();
	virtual void Attack();
	Enemy* GetEnemy();
private:
	void AreaAttack();
	Enemy *mEnemy;
};

#endif