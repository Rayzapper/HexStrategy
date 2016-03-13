#include "Game.h"
#include <iostream>

void Game::Run()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Hex Strategy");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
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

void Game::InternalClear()
{

}