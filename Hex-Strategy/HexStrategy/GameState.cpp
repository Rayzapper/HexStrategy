#include "GameState.h"
#include "GameStateManager.h"
#include "TextureManager.h"

GameState::GameState(GameStateManager *stateManager)
	: mGameStateManager(stateManager)
{

}

GameState::~GameState()
{

}

void GameState::ChangeState(GameState *state)
{
	mGameStateManager->SwitchState(state);
}

sf::Texture* GameState::GetTexture(int textureID) const
{
	return TextureManager::GetInstance().GetTexture(textureID);
}
