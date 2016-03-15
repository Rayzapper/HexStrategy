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
	virtual void Update(GameStateManager *stateManager);
	virtual void Render(sf::RenderWindow *window);
private:
	sf::Text splashText;
	sf::Font splashFont;
	sf::Clock mClock;
};

#endif