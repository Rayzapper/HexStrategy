#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "GameState.h"

class TitleState : public GameState
{
public:
	TitleState(GameStateManager *stateManager);
	virtual ~TitleState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos);
	virtual void Render(sf::RenderWindow *window);
};

#endif