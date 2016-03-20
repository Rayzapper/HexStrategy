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

Button::Button(sf::IntRect hitbox)
	: mHitBox(hitbox)
{

}

Button::~Button()
{
	
}

void Button::Update(sf::Vector2f mouseWorldPos)
{
	mMouseWorldPosition = sf::Vector2i(mouseWorldPos);
	mMouseOver = mHitBox.contains(mMouseWorldPosition);
	if (mMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		mPressed = true;
	if (mMouseOver && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		mRightPressed = true;
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

void Button::SetCharSize(int size)
{
	mButtonText.setCharacterSize(size);
}

bool Button::GetMouseover()
{
	return mMouseOver;
}

bool Button::GetClicked()
{
	bool clicked = false;
	if (mMouseOver && mPressed)
		clicked = !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	if (clicked || !mMouseOver)
		mPressed = false;
	return clicked;
}

bool Button::GetRightClicked()
{
	bool clicked = false;
	if (mMouseOver && mRightPressed && !mPressed)
		clicked = !sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
	if (clicked || !mMouseOver)
		mRightPressed = false;
	return clicked;
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