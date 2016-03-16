#include "PlayState.h"
#include <iostream>

Tile *selectedTile;

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
	currentLevel = new Level(GridVector(25, 18));
}

void PlayState::UnloadContent()
{
	
}

void PlayState::Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos)
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