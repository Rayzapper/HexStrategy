#ifndef BUFFED_H
#define BUFFED_H

#include "Enemy.h"

class Buffed : public Enemy
{
public:
	Buffed(Enemy *enemy);
	virtual ~Buffed();
	virtual void Walk();
	virtual void Attack();
	Enemy* GetEnemy();
private:
	void Flex();
	Enemy *mEnemy;
};

#endif