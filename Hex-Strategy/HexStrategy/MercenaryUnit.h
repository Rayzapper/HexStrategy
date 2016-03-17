#ifndef	MERCENARYUNIT_H
#define MERCENARYUNIT_H

#include "Unit.h"

class MercenaryUnit : public Unit
{
public:
	MercenaryUnit(GridVector gridVector, int team);
	~MercenaryUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif