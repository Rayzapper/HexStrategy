#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H

#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class DebugManager
{
public:
	static DebugManager& GetInstance();
	bool debugMode = false;
	void Render(sf::RenderWindow *window);
	void SetDebugString(string text);
	string GetDebugString();
private:
	DebugManager();
	DebugManager(const DebugManager &debugManager);
	DebugManager& operator=(const DebugManager &textureManager);
};

#endif