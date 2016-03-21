#ifndef SHAMANUNIT_H
#define SHAMANUNIT_H

#include "Unit.h"

class ShamanUnit : public Unit
{
public:
	ShamanUnit(GridVector gridVector, int team);
	~ShamanUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif