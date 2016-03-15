#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "GameState.h"

class TitleState : public GameState
{
public:
	TitleState();
	virtual ~TitleState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(GameStateManager *stateManager);
	virtual void Render(sf::RenderWindow *window);
private:
	sf::Text titleText;
	sf::Font titleFont;
};

#endif