#include "GameState.h"
#include "GameStateManager.h"

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