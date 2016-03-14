#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

using namespace std;

class Enemy
{
public:
	virtual ~Enemy();
	//Some example functions
	virtual void Walk() = 0;
	virtual void Attack() = 0;
};

#endif