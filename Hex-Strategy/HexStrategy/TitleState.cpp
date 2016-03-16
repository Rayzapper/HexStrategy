#include "TitleState.h"
#include "PlayState.h"
#include <iostream>

TitleState::TitleState()
{
	
}

TitleState::~TitleState()
{

}

void TitleState::LoadContent()
{
	if (!titleFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	titleText.setString("Hex Strategy");
	titleText.setFont(titleFont);
	titleText.setCharacterSize(50);
	titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
	titleText.setPosition(400, 100);
}

void TitleState::UnloadContent()
{

}

void TitleState::Update(GameStateManager *stateManager)
{
	GameState *state = new PlayState("");
	ChangeState(stateManager, state);
}

void TitleState::Render(sf::RenderWindow *window)
{
	window->draw(titleText);
}