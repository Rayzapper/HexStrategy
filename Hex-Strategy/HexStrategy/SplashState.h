#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "GameState.h"

class SplashState : public GameState
{
public:
	SplashState();
	virtual ~SplashState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update();
	virtual void Render(sf::RenderWindow *window);
};

#endif