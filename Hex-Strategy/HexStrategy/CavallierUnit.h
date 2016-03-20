#ifndef	CAVALLIERUNIT_H
#define CAVALLIERUNIT_H

#include "Unit.h"

class CavallierUnit : public Unit
{
public:
	CavallierUnit(GridVector gridVector, int team);
	~CavallierUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif