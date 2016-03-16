#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity
{
public:
	Unit(int textureID, GridVector gridVector);
	~Unit();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
	void SetGridPosition(GridVector position);
	GridVector GetGridPosition() const;
protected:
	int mTileSize = 32;
	GridVector mGridVector;
};

#endif