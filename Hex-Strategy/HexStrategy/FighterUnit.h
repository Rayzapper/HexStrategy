#ifndef	FIGHTERUNIT_H
#define FIGHTERUNIT_H

#include "Unit.h"

class FighterUnit : public Unit
{
public:
	FighterUnit(GridVector gridVector, int team);
	~FighterUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif