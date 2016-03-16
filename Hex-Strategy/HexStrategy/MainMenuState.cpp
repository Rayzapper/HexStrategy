#include "MainMenuState.h"
#include "PlayState.h"
#include "Button.h"
#include <cassert>

typedef vector<Entity*> EntityVector;
EntityVector mainButtonVector, optionsButtonVector;

enum SubMenu
{
	MAIN,
	OPTIONS
};

SubMenu subMenu = MAIN;

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

	mainButtonVector.push_back(new Button(sf::IntRect(100, 100, 600, 100), "Play", &mMenuButtonFont));
	mainButtonVector.push_back(new Button(sf::IntRect(100, 250, 600, 100), "Options", &mMenuButtonFont));
	mainButtonVector.push_back(new Button(sf::IntRect(100, 400, 600, 100), "Quit", &mMenuButtonFont));

	optionsButtonVector.push_back(new Button(sf::IntRect(100, 100, 600, 100), "Back", &mMenuButtonFont));
}

void MainMenuState::UnloadContent()
{
	while (!mainButtonVector.empty())
	{
		delete mainButtonVector.back();
		mainButtonVector.pop_back();
	}
}

void MainMenuState::Update(sf::Vector2f mouseWorldPos)
{
	EntityVector *entityVector;
	if (subMenu == MAIN)
		entityVector = &mainButtonVector;
	else
		entityVector = &optionsButtonVector;
	for each (Entity *e in *entityVector)
	{
		if (Button *b = dynamic_cast<Button*>(e))
		{
			b->Update(mouseWorldPos);
			if (b->GetClicked())
			{
				string buttonString = b->GetButtonString();
				if (buttonString == "Play")
				{
					GameState *state = new PlayState(mGameStateManager, "TestLevel");
					ChangeState(state);
					break;
				}
				else if (buttonString == "Options")
				{
					subMenu = OPTIONS;
					break;
				}
				else if (buttonString == "Quit")
				{
					mWindow->close();
					break;
				}
				else if (buttonString == "Back")
				{
					subMenu = MAIN;
					break;
				}
			}
		}
	}
}

void MainMenuState::Render(sf::RenderWindow *window)
{
	mWindow = window;
	if (subMenu == MAIN)
		for each (Button *b in mainButtonVector)
			b->Render(window);
	else if (subMenu == OPTIONS)
		for each (Button *b in optionsButtonVector)
			b->Render(window);
}