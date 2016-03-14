#include <iostream>
#include "Goblin.h"
#include "Boss.h"
#include "Buffed.h"

using namespace std;

int main()
{
	Goblin *gobbo1, *gobbo2;
	Boss *bossGobbo, *bossGobbo2;
	gobbo1 = new Goblin("Bob", 2, 4);
	gobbo2 = new Goblin("Bill", 4, 4);
	bossGobbo = new Boss(new Goblin("Bert", 3, 5));
	// Bill got promoted!
	bossGobbo2 = new Boss(gobbo2);
	// Bob got buffed!
	Buffed *buffBob = new Buffed(gobbo1);
	// then promoted
	Boss *bossBob = new Boss(buffBob);
	// Bert Attacks!
	bossGobbo->Attack();
	// Bob moves!
	bossBob->Walk();
	// Bill got demoted.
	Goblin *gobbo3 = new Goblin((Goblin*)bossGobbo2->GetEnemy());
	delete bossGobbo2;
	// and then checks where he is.
	cout << "Bill x position: " << gobbo3->GetXPos() << endl;
	cout << "Bill y position: " << gobbo3->GetYPos() << endl;
	// Bob gets demoted.
	Buffed *gobbo4 = new Buffed(new Goblin((Goblin*)bossBob->GetEnemy()));
	delete bossBob;
	// but is still buffed.
	gobbo4->Attack();
	return 0;
}