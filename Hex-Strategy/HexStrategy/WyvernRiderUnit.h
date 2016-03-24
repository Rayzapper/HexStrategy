#ifndef WYVERNRIDERUNIT_H
#define WYVERNRIDERUNIT_H

#include "Unit.h"

class WyvernRiderUnit : public Unit
{
public:
	WyvernRiderUnit(GridVector gridVector, int team);
	~WyvernRiderUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif