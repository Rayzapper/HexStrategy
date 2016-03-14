#include "Game.h"
#include "Level.h"
#include <iostream>
#include <string>

static const string programName = "Hex Strategy";
static const int tileSize = 40;

static int windowWidth = 200, windowHeight = 200;
static bool focus = true;

static sf::RenderWindow *window;

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
			Update();
			Render();
		}
		else
		{
			sf::Time time = sf::milliseconds(10);
			sf::sleep(time);
		}
	}
}

Game& Game::GetInstance()
{
	static Game game;
	return game;
}

Game::Game()
{
	
}

Game::~Game()
{
	InternalClear();
}

void Game::Initialize()
{
	Entity::Initialize();
}

void Game::InternalClear()
{

}

void Game::Update()
{

}

void Game::Render()
{
	window->clear();

	window->display();
}