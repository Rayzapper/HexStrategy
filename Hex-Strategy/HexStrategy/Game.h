#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	void Initialize();
	void InternalClear();
	void Update(float dt);
	void Render();
};

#endif