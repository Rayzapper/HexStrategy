#ifndef GARGOYLEUNIT_H
#define GARGOYLEUNIT_H

#include "Unit.h"

class GargoyleUnit : public Unit
{
public:
	GargoyleUnit(GridVector gridVector, int team);
	~GargoyleUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif