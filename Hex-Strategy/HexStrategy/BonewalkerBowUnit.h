#ifndef	BONEWALKERBOWUNIT_H
#define BONEWALKERBOWUNIT_H

#include "Unit.h"

class BonewalkerBowUnit : public Unit
{
public:
	BonewalkerBowUnit(GridVector gridVector, int team);
	~BonewalkerBowUnit();
	//virtual void Update(sf::Vector2f mouseWorldPos);
	//virtual void Render(sf::RenderWindow *window);
};

#endif