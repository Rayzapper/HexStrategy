#include "DebugManager.h"

static string debugString;
static sf::Font debugFont;
static sf::Text debugText;

DebugManager& DebugManager::GetInstance()
{
	static DebugManager debugManager;
	return debugManager;
}

void DebugManager::Render(sf::RenderWindow *window)
{
	debugText.setString(debugString);
	window->draw(debugText);
}

void DebugManager::SetDebugString(string text)
{
	debugString = text;
}

string DebugManager::GetDebugString()
{
	return debugString;
}

DebugManager::DebugManager()
{
	debugText.setCharacterSize(16);
	debugText.setString(debugString);
	debugText.setColor(sf::Color::Magenta);

	if (!debugFont.loadFromFile("Resources/Fonts/calibri.ttf"))
		cout << "Could not find font calibri.ttf" << endl;
	debugText.setFont(debugFont);
}