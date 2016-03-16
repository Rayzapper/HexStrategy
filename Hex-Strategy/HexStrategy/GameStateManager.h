#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <stack>
#include "SplashState.h"
#include "TitleState.h"
#include "PlayState.h"

class GameStateManager
{
public:
	~GameStateManager();
	static GameStateManager& GetInstance();

	typedef std::stack<GameState*> GameStates;

	void Initialize();
	void LoadContent();
	void Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos);
	void Render(sf::RenderWindow *window);

	void PushState(GameState *state);
	void PopState();
	void SwitchState(GameState *state);
private:
	GameStateManager();
	GameStateManager(const GameStateManager &gameStateManager);	
	GameStateManager& operator=(const GameStateManager &textureManager);
};

#endif