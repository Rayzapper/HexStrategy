#include "Button.h"
#include <iostream>

Button::Button(int textureID, sf::IntRect hitbox, std::string buttonText, sf::Font *font)
	: UIElement(textureID),
	mHitBox(hitbox),
	mButtonString(buttonText),
	mFont(font)
{
	Setup();
}

Button::Button(sf::IntRect hitbox, std::string buttonText, sf::Font *font)
	: mHitBox(hitbox),
	mButtonString(buttonText),
	mFont(font)
{
	Setup();
}

Button::~Button()
{
	
}

void Button::Update()
{
	mMouseOver = mHitBox.contains(mMouseWindowPosition);
}

void Button::UpdateMousePosition(sf::Vector2i mouseWindowPos)
{
	mMouseWindowPosition = mouseWindowPos;
}

void Button::Render(sf::RenderWindow *window)
{
	window->draw(mShape);
	window->draw(mButtonText);
}

void Button::SetFont(sf::Font *font)
{
	mFont = font;
	mButtonText.setFont(*mFont);
}

bool Button::GetPressed() const
{
	if (mMouseOver)
		return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	else
		return false;
}

std::string Button::GetButtonString() const
{
	return mButtonString;
}

void Button::Setup()
{
	mShape.setSize(sf::Vector2f(mHitBox.width, mHitBox.height));
	mShape.setPosition(mHitBox.left, mHitBox.top);
	mShape.setFillColor(sf::Color::Blue);
	mShape.setOutlineColor(sf::Color::White);
	mShape.setOutlineThickness(-2);

	mButtonText.setFont(*mFont);
	mButtonText.setString(mButtonString);
	mButtonText.setColor(sf::Color::White);
	mButtonText.setCharacterSize(30);
	mButtonText.setOrigin(mButtonText.getLocalBounds().width / 2, mButtonText.getLocalBounds().height / 2);
	mButtonText.setPosition(mShape.getPosition().x + mShape.getSize().x / 2, mShape.getPosition().y + mShape.getSize().y / 2);
}