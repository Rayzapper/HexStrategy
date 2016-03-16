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
	virtual void Update(sf::Vector2f mouseWorldPos) = 0;
	virtual void Render(sf::RenderWindow *window) = 0;
	void ChangeState(GameState *state);
protected:
	sf::Texture* GetTexture(int textureID) const;
	GameStateManager *mGameStateManager;
};

#endif