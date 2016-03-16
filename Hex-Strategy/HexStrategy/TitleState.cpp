#include "TitleState.h"
#include "MainMenuState.h"
#include <iostream>

static const int fadeSpeed = 4;

int enterTextAlpha = 0;
bool fadein = true;

sf::Font titleFont, enterFont;
sf::Texture titleGraphicTexture;

sf::Text titleText, enterText;
sf::Sprite titleGraphicSprite;

TitleState::TitleState(GameStateManager *stateManager)
	: GameState(stateManager)
{
	
}

TitleState::~TitleState()
{

}

void TitleState::LoadContent()
{
	if (!titleFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	if (!enterFont.loadFromFile("Resources/Fonts/Fire Emblem 8 Text.ttf"))
		cout << "Could not find font Fire Emblem 8 Text.ttf" << endl;
	if (!titleGraphicTexture.loadFromFile("Resources/Graphics/TitleGraphic.png"))
		cout << "Could not find image TitleGraphic.png" << endl;

	titleText.setString("Hex Strategy");
	titleText.setFont(titleFont);
	titleText.setCharacterSize(96);
	titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
	titleText.setPosition(400, 200);
	titleText.setColor(sf::Color(140, 60, 40, 255));
	titleText.setStyle(sf::Text::Bold);

	enterText.setString("Press Enter to continue");
	enterText.setFont(enterFont);
	enterText.setCharacterSize(32);
	enterText.setOrigin(enterText.getLocalBounds().width / 2, enterText.getLocalBounds().height / 2);
	enterText.setPosition(400, 400);
	enterText.setColor(sf::Color(100, 255, 100, enterTextAlpha));

	titleGraphicSprite.setTexture(titleGraphicTexture, true);
	titleGraphicSprite.setOrigin(titleGraphicTexture.getSize().x / 2, titleGraphicTexture.getSize().y / 2);
	titleGraphicSprite.setPosition(titleText.getPosition());
}

void TitleState::UnloadContent()
{

}

void TitleState::Update(sf::Vector2f mouseWorldPos, sf::Vector2i mouseWindowPos)
{
	if (fadein)
	{
		enterTextAlpha += fadeSpeed;
		if (enterTextAlpha > 255)
			enterTextAlpha = 255;
	}
	else
	{
		enterTextAlpha -= fadeSpeed;
		if (enterTextAlpha < 0)
			enterTextAlpha = 0;
	}
	if (enterTextAlpha <= 0 || enterTextAlpha >= 255)
		fadein = !fadein;
	enterText.setColor(sf::Color(100, 255, 100, enterTextAlpha));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		GameState *state = new MainMenuState(mGameStateManager);
		ChangeState(state);
	}
}

void TitleState::Render(sf::RenderWindow *window)
{
	window->draw(titleGraphicSprite);
	window->draw(titleText);
	window->draw(enterText);
}