#include "Game.h"
#include "Level.h"
#include "GameStateManager.h"
#include <iostream>
#include <string>

static const string programName = "Hex Strategy";
static const int tileSize = 32;

static int windowWidth = 800, windowHeight = 600;
static bool focus = true;
static sf::Vector2i mousePosition;

static sf::RenderWindow *window;
static sf::View *mainView, *debugView;

static sf::Font debugFont;
static sf::Text debugText;

Game::Game()
{

}

Game::~Game()
{
	InternalClear();
}

void Game::Run()
{
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), programName);
	window->setFramerateLimit(60);
	mainView = new sf::View(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(windowWidth, windowHeight));
	debugView = new sf::View(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(windowWidth, windowHeight));

	window->setView(*mainView);

	if (!debugFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	debugText.setFont(debugFont);
	debugText.setCharacterSize(16);
	debugText.setColor(sf::Color::Magenta);

	GameStateManager::GetInstance().Initialize();
	GameStateManager::GetInstance().LoadContent();
	
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::GainedFocus)
				focus = true;
			if (event.type == sf::Event::LostFocus)
				focus = false;
		}
		if (focus)
		{
			mousePosition = sf::Mouse::getPosition(*window);
			sf::Vector2f mouseWorldPosition = window->mapPixelToCoords(mousePosition, *mainView);
			
			GameStateManager::GetInstance().Update(mouseWorldPosition);
			debugText.setString("Mouse World X = " + to_string(mouseWorldPosition.x) + "\nMouse World Y = " + to_string(mouseWorldPosition.y));
			window->clear();
			GameStateManager::GetInstance().Render(window);
			window->setView(*debugView);
			window->draw(debugText);
			window->display();
			window->setView(*mainView);
		}
		else
		{
			sf::Time time = sf::milliseconds(10);
			sf::sleep(time);
		}
	}
}

void Game::Initialize()
{
	
}

void Game::InternalClear()
{

}