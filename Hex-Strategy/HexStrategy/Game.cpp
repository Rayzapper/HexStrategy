#include "Game.h"
#include "Level.h"
#include "GameStateManager.h"
#include <iostream>
#include <string>

static const string programName = "Hex Strategy";
static const int tileSize = 32;

static int windowWidth = 200, windowHeight = 200;
static bool focus = true;

static sf::RenderWindow *window;

static GameStateManager stateManager;

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
			Update(0);
			Render();
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
	Entity::Initialize();
}

void Game::InternalClear()
{

}

void Game::Update(float dt)
{
	stateManager.Update();
}

void Game::Render()
{
	window->clear();
	stateManager.Render(window);
	window->display();
}