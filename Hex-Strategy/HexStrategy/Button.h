#ifndef BUTTON_H
#define BUTTON_H

#include "UIElement.h"

class Button : public UIElement
{
public:
	//Texture version
	Button(int textureID, sf::IntRect hitbox, std::string buttonText, sf::Font *font);
	//No Texture version.
	Button(sf::IntRect hitbox, std::string buttonText, sf::Font *font);
	virtual ~Button();
	virtual void Update();
	void UpdateMousePosition(sf::Vector2i mouseWindowPos);
	virtual void Render(sf::RenderWindow *window);
	void SetFont(sf::Font *font);
	bool GetPressed() const;
	std::string GetButtonString() const;
private:
	void Setup();
	sf::IntRect mHitBox;
	bool mMouseOver;
	sf::RectangleShape mShape;
	sf::Font *mFont;
	sf::Text mButtonText;
	sf::Vector2i mMouseWindowPosition;
	std::string mButtonString;
};

#endif