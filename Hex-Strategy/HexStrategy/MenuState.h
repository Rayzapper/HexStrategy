#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MenuState : public GameState
{
public:
	MenuState(GameStateManager *stateManager);
	virtual ~MenuState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
private:
	sf::Font mMenuButtonFont;
};

#endif