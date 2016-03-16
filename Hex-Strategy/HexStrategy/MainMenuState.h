#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState(GameStateManager *stateManager);
	virtual ~MainMenuState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos);
	virtual void Render(sf::RenderWindow *window);
private:
	sf::Font mMenuButtonFont;
};

#endif