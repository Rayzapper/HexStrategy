#include "GameState.h"
#include "GameStateManager.h"

GameState::GameState()
{

}

GameState::~GameState()
{

}

void GameState::ChangeState(GameStateManager *stateManager, GameState *state)
{
	stateManager->SwitchState(state);
}