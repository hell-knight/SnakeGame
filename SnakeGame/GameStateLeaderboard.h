#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	struct Game;

	struct GameStateLeaderboardData
	{
		sf::Font font;

		sf::Text hintText;
		sf::Text recordsTableText;
	};

	// Returns pointer to the allocated data
	void InitGameStateLeaderboard(GameStateLeaderboardData& data, Game& game);
	void ShutdownGameStateLeaderboard(GameStateLeaderboardData& data, Game& game);
	void HandleGameStateLeaderboardWindowEvent(GameStateLeaderboardData& data, Game& game, const sf::Event& event);
	void UpdateGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, float deltaTime);
	void DrawGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, sf::RenderWindow& window);
}