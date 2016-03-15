#include "GameStateManager.h"
#include <cassert>

GameStateManager::GameStates stateStack;

GameStateManager::~GameStateManager()
{

}

GameStateManager& GameStateManager::GetInstance()
{
	static GameStateManager manager;
	return manager;
}

void GameStateManager::Initialize()
{
	stateStack.push(new SplashState());
}

void GameStateManager::LoadContent()
{
	stateStack.top()->LoadContent();
}

void GameStateManager::Update()
{
	if (stateStack.top() == nullptr)
		stateStack.pop();
	assert(!stateStack.empty());
	stateStack.top()->Update(this);
}

void GameStateManager::Render(sf::RenderWindow *window)
{
	assert(!stateStack.empty());
	stateStack.top()->Render(window);
}

void GameStateManager::PushState(GameState *state)
{
	stateStack.push(state);
	stateStack.top()->LoadContent();
}

void GameStateManager::PopState()
{
	assert(stateStack.size() > 1);
	stateStack.top()->UnloadContent();
	delete stateStack.top();
	stateStack.pop();
}

void GameStateManager::SwitchState(GameState *state)
{
	stateStack.top()->UnloadContent();
	delete stateStack.top();
	stateStack.pop();
	stateStack.push(state);
	stateStack.top()->LoadContent();
}

GameStateManager::GameStateManager()
{

}
