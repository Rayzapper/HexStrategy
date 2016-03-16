#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "GameState.h"

class SplashState : public GameState
{
public:
	SplashState(GameStateManager *stateManager);
	virtual ~SplashState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos);
	virtual void Render(sf::RenderWindow *window);
private:
	sf::Text splashText;
	sf::Font splashFont;
	sf::Clock mClock;
};

#endif