#include "GameStateLeaderboard.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStateLeaderboard(GameStateLeaderboardData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.recordsTableText.setFont(data.font);
		data.recordsTableText.setCharacterSize(24);
		data.recordsTableText.setFillColor(sf::Color::White);
		data.recordsTableText.setString("Records:");
		std::vector<Record> sortedTable = BuildSortedRecords(game.leaderboard);
		for (int i = 0; i < RECORDS_MAIN_MENU; ++i)
		{
			data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + std::to_string(i + 1) + ".   " + sortedTable[i].name + ": " + std::to_string(sortedTable[i].score));
		}
	}

	void ShutdownGameStateLeaderboard(GameStateLeaderboardData& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleGameStateLeaderboardWindowEvent(GameStateLeaderboardData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (static_cast<uint32_t>(game.gameSettings) & static_cast<uint32_t>(GameSettings::sound))
			{
				game.pressButtonSound.play();
			}
			if (event.key.code == sf::Keyboard::B)
			{
				SwitchGameState(game, GameStateType::MainMenu);
			}
		}
	}

	void UpdateGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, float deltaTime)
	{
		data.recordsTableText.setOrigin(GetTextOrigin(data.recordsTableText, { 0.5f, 0.f }));
	}

	void DrawGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		data.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
		window.draw(data.recordsTableText);

	}

}