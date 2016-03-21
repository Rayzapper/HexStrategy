#ifndef REVENANTUNIT_H
#define REVENANTUNIT_H

#include "Unit.h"

class RevenantUnit : public Unit
{
public:
	RevenantUnit(GridVector gridVector, int team);
	~RevenantUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif