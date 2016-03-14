#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"
#include <SFML/Graphics.hpp>

class GameState
{
public:
	GameState();
	virtual ~GameState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update();
	virtual void Render(sf::RenderWindow *window);
};

#endif