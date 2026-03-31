#pragma once
#include "SFML/Graphics.hpp"
#include "Apple.h"
#include "Player.h"
#include "Wall.h"
#include "GridGame.h"
#include "Stone.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// Resources
		sf::Texture appleTexture;
		sf::Texture stoneTexture;
		sf::Font font;
		sf::Music backgroundMusic;

		// Game data
		float moveTimer = 0.f;
		int pointLevel = LEVEL_COEFFICIENT_ONE;
		float gameOffsetY = TOP_PANEL_SIZE;
		// player data
		int score = 0;
		Player player;
		bool isDying = false;
		float deathTimer = 0.f;
		float currentSpeed = 0.f;
		// apples data
		Apple apple;
		float poisonTimer = 0.f;
		float disorientTimer = 0.f;
		// stones data
		std::vector<Stone> stones;
		// wall data
		std::vector<Wall> wall;
		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape topPanel;

		Grid grid;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
	
	void HandleInput(GameStatePlayingData& data);
	void InitGameModeSettings(GameStatePlayingData& data, const uint32_t gameMode);
	void SpawnTemporaryStone(GameStatePlayingData& data, Grid& grid);
}