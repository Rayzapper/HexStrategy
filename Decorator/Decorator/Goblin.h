#ifndef GOBLIN_H
#define GOBLIN_H

#include "Enemy.h"

class Goblin : public Enemy
{
public:
	Goblin(string name, int xPosition, int yPosition);
	Goblin(Goblin *goblin);
	//Some example functions
	virtual void Walk();
	virtual void Attack();
	string GetName();
	int GetXPos();
	int GetYPos();
private:
	Enemy *mEnemy;
	int mXPos, mYPos;
	string mName;
};

#endif