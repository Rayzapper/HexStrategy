#include "Buffed.h"

Buffed::Buffed(Enemy *enemy)
	: mEnemy(enemy)
{

}

Buffed::~Buffed()
{
	delete mEnemy;
}

void Buffed::Walk()
{
	mEnemy->Walk();
}

void Buffed::Attack()
{
	Flex();
	mEnemy->Attack();
}

Enemy* Buffed::GetEnemy()
{
	return mEnemy;
}

void Buffed::Flex()
{
	cout << "Flexing ";
}