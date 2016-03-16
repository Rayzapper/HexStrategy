#include "Unit.h"

Unit::Unit(int textureID)
	: Entity(textureID)
{

}

Unit::~Unit()
{

}

void Unit::Update()
{

}

void Unit::Render(sf::RenderWindow *window)
{

}

void Unit::SetGridPosition(GridVector position)
{
	mGridVector = position;
}

GridVector Unit::GetGridPosition() const
{
	return mGridVector;
}