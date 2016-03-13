#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	virtual ~Entity();
	virtual void Update() = 0;
	virtual void Render() = 0;
};

#endif