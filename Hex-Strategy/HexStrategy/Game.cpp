#include "Game.h"
#include "Level.h"
#include "GameStateManager.h"
#include <iostream>
#include <string>

static const string programName = "Hex Strategy";
static const int tileSize = 32;

static int windowWidth = 800, windowHeight = 600;
static bool focus = true;

static sf::RenderWindow *window;
static sf::View *mainView, *uiView;

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
	uiView = new sf::View(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(windowWidth, windowHeight));

	window->setView(*mainView);

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
			GameStateManager::GetInstance().Update();
			window->clear();
			GameStateManager::GetInstance().Render(window);
			window->display();
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