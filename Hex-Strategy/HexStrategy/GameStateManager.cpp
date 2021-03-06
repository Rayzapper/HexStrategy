#include "GameStateManager.h"
#include <cassert>

static GameStateManager::GameStates stateStack;

GameStateManager::~GameStateManager()
{

}

GameStateManager& GameStateManager::GetInstance()
{
	static GameStateManager manager;
	return manager;
}

void GameStateManager::Initialize(sf::RenderWindow *window)
{
	mWindow = window;
	stateStack.push(new SplashState(this));
}

void GameStateManager::LoadContent()
{
	stateStack.top()->LoadContent();
}

void GameStateManager::Update(sf::Vector2f mouseWorldPos)
{
	if (stateStack.top() == nullptr)
		stateStack.pop();
	assert(!stateStack.empty());
	stateStack.top()->Update(mouseWorldPos);
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

sf::RenderWindow* GameStateManager::GetWindow() const
{
	return mWindow;
}

GameStateManager::GameStateManager()
{

}