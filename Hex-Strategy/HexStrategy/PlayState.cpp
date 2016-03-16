#include "PlayState.h"
#include "UIElement.h"
#include <iostream>

struct Selector
{
	GridVector gridPosition;
	sf::Vector2f renderPosition;
	UIElement selectorBit1;
	UIElement selectorBit2;
	UIElement selectorBit3;
	UIElement selectorBit4;
	static sf::Texture *texture;
	sf::Sprite sprite;
	int animationOffset = 0;
	bool render = false;
	void Render(sf::RenderWindow *window)
	{
		window->draw(sprite);
		sprite.rotate(90);
		window->draw(sprite);
		sprite.rotate(90);
		window->draw(sprite);
		sprite.rotate(90);
		window->draw(sprite);
		sprite.rotate(90);
	}
};

Tile *selectedTile;
Selector selector;

PlayState::PlayState(GameStateManager *stateManager, string levelName)
	: GameState(stateManager)
{
	
}

PlayState::~PlayState()
{

}

void PlayState::LoadContent()
{
	if (!playFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	currentLevel = new Level(GridVector(25, 18));
	selector.texture = GetTexture(2);
	selector.sprite.setTexture(*selector.texture);
}

void PlayState::UnloadContent()
{
	
}

void PlayState::Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos)
{
	currentLevel->Update(mouseWorldPos);
}

void PlayState::Render(sf::RenderWindow *window)
{
	currentLevel->Render(window);
	if (selector.render)
		selector.Render(window);
}

void PlayState::SwitchLevel(Level *level)
{
	delete currentLevel;
	currentLevel = level;
}