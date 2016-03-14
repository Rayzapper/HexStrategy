#include "Goblin.h"

Goblin::Goblin(string name, int xPosition, int yPosition)
	: mName(name), mXPos(xPosition), mYPos(yPosition)
{
	
}

Goblin::Goblin(Goblin *goblin)
	: mName(goblin->GetName()), mXPos(goblin->GetXPos()), mYPos(goblin->GetYPos())
{

}

void Goblin::Walk()
{
	cout << "Goblin walks one tile forward." << endl;
}

void Goblin::Attack()
{
	cout << "Goblin attacks." << endl;
}

string Goblin::GetName()
{
	return mName;
}

int Goblin::GetXPos()
{
	return mXPos;
}

int Goblin::GetYPos()
{
	return mYPos;
}