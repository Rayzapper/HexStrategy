#include "GameStateManager.h"

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
	stateStack.top()->Update();
}

void GameStateManager::Render(sf::RenderWindow * window)
{
	stateStack.top()->Render(window);
}

GameStateManager::GameStateManager()
{

}