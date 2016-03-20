#ifndef ARCHERUNIT_H
#define ARCHERUNIT_H

#include "Unit.h"

class ArcherUnit : public Unit
{
public:
	ArcherUnit(GridVector gridVector, int team);
	~ArcherUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif