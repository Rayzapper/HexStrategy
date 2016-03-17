#ifndef	BONEWALKERSWORDUNIT_H
#define BONEWALKERSWORDUNIT_H

#include "Unit.h"

class BonewalkerSwordUnit : public Unit
{
public:
	BonewalkerSwordUnit(GridVector gridVector, int team);
	~BonewalkerSwordUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif