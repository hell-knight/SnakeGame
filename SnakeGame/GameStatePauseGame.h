#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePauseGameData
	{
		sf::Font font;

		MenuItem resume;
		MenuItem exitMainMenu;

		Menu menu;
	};

	// Returns pointer to the allocated data
	void InitGameStatePauseGame(GameStatePauseGameData& data, Game& game);
	void ShutdownGameStatePauseGame(GameStatePauseGameData& data, Game& game);
	void HandleGameStatePauseGameWindowEvent(GameStatePauseGameData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePauseGame(GameStatePauseGameData& data, Game& game, float deltaTime);
	void DrawGameStatePauseGame(GameStatePauseGameData& data, Game& game, sf::RenderWindow& window);
}