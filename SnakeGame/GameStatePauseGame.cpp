#include "GameStatePauseGame.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void InitGameStatePauseGame(GameStatePauseGameData& data, Game& game)
	{
		if (game.gameSettings & static_cast<uint32_t>(GameSettings::music))
		{
			game.backgroundMusic.pause();
		}

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.menu.rootItem.hintText.setString("PAUSE");
		data.menu.rootItem.hintText.setFont(data.font);
		data.menu.rootItem.hintText.setCharacterSize(48);
		data.menu.rootItem.hintText.setFillColor(sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Horizontal;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 100.f;
		data.menu.rootItem.children.push_back(&data.resume);
		data.menu.rootItem.children.push_back(&data.exitMainMenu);

		data.resume.text.setString("Resume");
		data.resume.text.setFont(data.font);
		data.resume.text.setCharacterSize(24);

		data.exitMainMenu.text.setString("Exit MainMenu");
		data.exitMainMenu.text.setFont(data.font);
		data.exitMainMenu.text.setCharacterSize(24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.resume);
	}

	void ShutdownGameStatePauseGame(GameStatePauseGameData& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleGameStatePauseGameWindowEvent(GameStatePauseGameData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				if (game.gameSettings & static_cast<uint32_t>(GameSettings::music))
				{
					game.backgroundMusic.play();
				}
				if (static_cast<uint32_t>(game.gameSettings) & static_cast<uint32_t>(GameSettings::sound))
				{
					game.pressButtonSound.play();
				}
				if (data.menu.selectedItem == &data.resume)
				{
					game.pauseTimeStartGame = PAUSE_TIME_START_GAME;
					PopGameState(game);
				}
				else if (data.menu.selectedItem == &data.exitMainMenu)
				{
					SwitchGameState(game, GameStateType::MainMenu);
				}
			}
		}

		Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
		if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
			orientation == Orientation::Vertical && event.key.code == sf::Keyboard::W ||
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left ||
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::A)
		{
			SelectPreviousMenuItem(data.menu);
		}
		else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
			orientation == Orientation::Vertical && event.key.code == sf::Keyboard::S ||
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right ||
			orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::D)
		{
			SelectNextMenuItem(data.menu);
		}
	}

	void UpdateGameStatePauseGame(GameStatePauseGameData& data, Game& game, float deltaTime)
	{
		
	}

	void DrawGameStatePauseGame(GameStatePauseGameData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}

}