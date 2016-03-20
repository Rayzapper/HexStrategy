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

	void Initialize(sf::RenderWindow *window);
	void LoadContent();
	void Update(sf::Vector2f mouseWorldPos);
	void Render(sf::RenderWindow *window);

	void PushState(GameState *state);
	void PopState();
	void SwitchState(GameState *state);

	sf::RenderWindow* GetWindow() const;
private:
	GameStateManager();
	GameStateManager(const GameStateManager &gameStateManager);	
	GameStateManager& operator=(const GameStateManager &textureManager);
	sf::RenderWindow *mWindow;
};

#endif