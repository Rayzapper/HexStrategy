#ifndef	MAGEUNIT_H
#define MAGEUNIT_H

#include "Unit.h"

class MageUnit : public Unit
{
public:
	MageUnit(GridVector gridVector, int team);
	~MageUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif