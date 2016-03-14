#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

using namespace std;

class Game
{
public:
	void Run();
	static Game& GetInstance();			//Singleton
private:
	Game();								//Singleton
	Game(const Game &game);				//Singleton
	Game& operator=(const Game &game);	//Singleton
	~Game();
	void Initialize();
	void InternalClear();
	void Update();
	void Render();
};

#endif