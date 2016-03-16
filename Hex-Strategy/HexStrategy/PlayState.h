#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "Level.h"

class PlayState : public GameState
{
public:
	PlayState(GameStateManager *stateManager, string levelName);
	virtual ~PlayState();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos);
	virtual void Render(sf::RenderWindow *window);
	void SwitchLevel(Level *level);
private:
	sf::Font playFont;
	sf::Texture mMercenaryTexture, mTilesTexture;
	Level *currentLevel;
};

#endif