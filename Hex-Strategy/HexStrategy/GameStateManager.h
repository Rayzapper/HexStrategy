#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <stack>
#include "SplashState.h"

class GameStateManager
{
public:
	~GameStateManager();
	static GameStateManager& GetInstance();

	typedef std::stack<GameState*> GameStates;

	void Initialize();
	void LoadContent();
	void Update();
	void Render(sf::RenderWindow *window);
private:
	GameStateManager();
	GameStateManager(const GameStateManager &gameStateManager);	
	GameStateManager& operator=(const GameStateManager &textureManager);
};

#endif