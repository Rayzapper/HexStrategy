#ifndef TARVOSUNIT_H
#define TARVOSUNIT_H

#include "Unit.h"

class TarvosUnit : public Unit
{
public:
	TarvosUnit(GridVector gridVector, int team);
	~TarvosUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif