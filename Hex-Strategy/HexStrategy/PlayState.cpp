#include "PlayState.h"
#include "UIElement.h"
#include <iostream>

static const int tileSize = 32;

struct Selector
{
	GridVector gridPosition;
	sf::Vector2f renderPosition;
	sf::Texture *texture;
	sf::Sprite sprite;
	int animationOffset = 0;
	void Render(sf::RenderWindow *window)
	{
		sprite.setPosition(gridPosition.x * tileSize + 16, gridPosition.y * tileSize / 2 + 16);
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
	selector.sprite.setOrigin(tileSize / 2 + 4, tileSize / 2 + 4);
}

void PlayState::UnloadContent()
{
	
}

void PlayState::Update(sf::Vector2f mouseWorldPos)
{
	currentLevel->Update(mouseWorldPos);
	selector.gridPosition = currentLevel->GetMouseoverPosition();
}

void PlayState::Render(sf::RenderWindow *window)
{
	currentLevel->Render(window);
	selector.Render(window);
}

void PlayState::SwitchLevel(Level *level)
{
	delete currentLevel;
	currentLevel = level;
}