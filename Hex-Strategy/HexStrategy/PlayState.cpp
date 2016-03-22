#include "PlayState.h"
#include "UIElement.h"
#include "MainMenuState.h"
#include <iostream>

static const int tileSize = 32;

PlayState::PlayState(GameStateManager *stateManager, string levelName)
	: GameState(stateManager)
{
	
}

PlayState::~PlayState()
{

}

void PlayState::LoadContent()
{
	if (!playFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	currentLevel = new Level(GridVector(25, 36), GetWindow());
}

void PlayState::UnloadContent()
{
	delete currentLevel;
}

void PlayState::Update(sf::Vector2f mouseWorldPos)
{
	currentLevel->Update(mouseWorldPos);
	if (currentLevel->GetSubState() == LEVELOVER)
		ChangeState(new MainMenuState(mGameStateManager));
}

void PlayState::Render(sf::RenderWindow *window)
{
	currentLevel->Render(window);
}

void PlayState::SwitchLevel(Level *level)
{
	delete currentLevel;
	currentLevel = level;
}