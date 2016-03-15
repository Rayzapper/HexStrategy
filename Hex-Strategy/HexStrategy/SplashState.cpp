#include "SplashState.h"
#include "TitleState.h"
#include <iostream>

SplashState::SplashState()
{
	
}

SplashState::~SplashState()
{

}

void SplashState::LoadContent()
{
	if (!splashFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	splashText.setString("SplashScreen");
	splashText.setFont(splashFont);
	mClock.restart();
}

void SplashState::UnloadContent()
{
	
}

void SplashState::Update(GameStateManager *stateManager)
{
	int time = mClock.getElapsedTime().asSeconds();
	if (time >= 3)
	{
		GameState *state = new TitleState();
		ChangeState(stateManager, state);
	}
}

void SplashState::Render(sf::RenderWindow *window)
{
	window->draw(splashText);
}