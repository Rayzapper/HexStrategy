#include "PlayState.h"
#include <iostream>

PlayState::PlayState(string levelName)
{
	
}

PlayState::~PlayState()
{

}

void PlayState::LoadContent()
{
	if (!playFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	currentLevel = new Level(GridVector(10, 10));
}

void PlayState::UnloadContent()
{
	
}

void PlayState::Update(GameStateManager *stateManager)
{
	currentLevel->Update();
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