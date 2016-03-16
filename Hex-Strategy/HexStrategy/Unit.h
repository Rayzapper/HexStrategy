#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity
{
public:
	Unit(int textureID);
	~Unit();
	virtual void Update();
	virtual void Render(sf::RenderWindow *window);
	void SetGridPosition(GridVector position);
	GridVector GetGridPosition() const;
private:
	GridVector mGridVector;
};

#endif