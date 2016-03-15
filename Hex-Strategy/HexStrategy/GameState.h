#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

using namespace std;

class GameStateManager;

class GameState
{
public:
	GameState();
	virtual ~GameState();
	virtual void LoadContent() = 0;
	virtual void UnloadContent() = 0;
	virtual void Update(GameStateManager *stateManager) = 0;
	virtual void Render(sf::RenderWindow *window) = 0;
	void ChangeState(GameStateManager *stateManager, GameState *state);
};

#endif