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
	titleText.setString("TitleScreen");
	titleText.setFont(titleFont);
}

void TitleState::UnloadContent()
{

}

void TitleState::Update(GameStateManager *stateManager)
{

}

void TitleState::Render(sf::RenderWindow *window)
{
	window->draw(titleText);
}