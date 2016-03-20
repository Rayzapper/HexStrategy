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
	//No Graphic version.
	Button(sf::IntRect hitbox);
	virtual ~Button();
	virtual void Update(sf::Vector2f mouseWorldPos);
	virtual void Render(sf::RenderWindow *window);
	void SetFont(sf::Font *font);
	void SetCharSize(int size);
	bool GetMouseover();
	bool GetClicked();
	bool GetRightClicked();
	std::string GetButtonString() const;
private:
	void Setup();
	sf::IntRect mHitBox;
	bool mMouseOver = false, mPressed, mRightPressed;
	sf::RectangleShape mShape;
	sf::Font *mFont;
	sf::Text mButtonText;
	sf::Vector2i mMouseWorldPosition;
	std::string mButtonString;
};

#endif