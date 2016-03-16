#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class GameStateManager;

class GameState
{
public:
	GameState(GameStateManager *stateManager);
	virtual ~GameState();
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	virtual void Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos) = 0;
	virtual void Render(sf::RenderWindow *window) = 0;
	void ChangeState(GameState *state);
protected:
	GameStateManager *mGameStateManager;
};

#endif