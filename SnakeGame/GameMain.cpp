#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Constants.h"
#include "Game.h"
#include <ctime>

using namespace SnakeGame;

int main()
{
	// Init random number generator
	int seed = (int)time(nullptr);
	srand(seed);

	// init window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");

	// We now use too much memory for stack, so we need to allocate it on heap
	SnakeGame::Game* game = new SnakeGame::Game();
	// game initialization
	InitGame(*game);

	// init game clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		// reduce framerate to not spam CPU and GPU
		sf::sleep(sf::milliseconds(16));


		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		// Calculate time Delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		// update game state
		if (UpdateGame(*game, deltaTime))
		{
			// draw game
			window.clear();
			DrawGame(*game, window);

			window.display();
		}
		else
		{
			window.close();
		}
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;

	return 0;
}