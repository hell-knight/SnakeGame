#pragma once
#include <SFML/Audio.hpp>
#include "SFML/Graphics.hpp"
#include "Menu.h"

namespace SnakeGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem startGameItem;
		MenuItem leaderboardItem;
		MenuItem levelItem;
		MenuItem settingsItem;
		MenuItem easyItem;
		MenuItem easyMiddleItem;
		MenuItem middleItem;
		MenuItem middleHardItem;
		MenuItem hardItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;
		MenuItem soundItem;
		MenuItem musicItem;
		MenuItem withoutStoneItem;
		MenuItem withStoneItem;
		MenuItem someTimeStoneItem;
		Menu menu;
	};

	// Returns pointer to the allocated data
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float deltaTime);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}