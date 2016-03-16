#include "MainMenuState.h"
#include "PlayState.h"
#include "Button.h"
#include <cassert>

typedef vector<Button> ButtonVector;
ButtonVector buttonVector;

MainMenuState::MainMenuState(GameStateManager *stateManager)
	: GameState(stateManager)
{
	
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::LoadContent()
{
	if (!mMenuButtonFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;

	buttonVector.push_back(Button(sf::IntRect(100, 100, 600, 100), "Play", &mMenuButtonFont));
	buttonVector.push_back(Button(sf::IntRect(100, 250, 600, 100), "Options", &mMenuButtonFont));
	buttonVector.push_back(Button(sf::IntRect(100, 400, 600, 100), "Quit", &mMenuButtonFont));
}

void MainMenuState::UnloadContent()
{
	
}

void MainMenuState::Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos)
{
	for each (Button b in buttonVector)
	{
		b.UpdateMousePosition(mouseWindowPos);
		b.Update();
	}
	for each (Button b in buttonVector)
	{
		if (b.GetPressed())
		{
			string buttonString = b.GetButtonString();
			if (buttonString == "Play")
			{
				GameState *state = new PlayState(mGameStateManager, "TestLevel");
				ChangeState(state);
			}
			else if (buttonString == "Options")
			{

			}
			else if (buttonString == "Quit")
			{

			}
		}
	}
}

void MainMenuState::Render(sf::RenderWindow *window)
{
	for each (Button b in buttonVector)
		b.Render(window);
}