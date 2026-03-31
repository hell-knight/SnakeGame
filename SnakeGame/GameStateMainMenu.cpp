#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>
#include <iostream>

namespace SnakeGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		auto setTextParameters = [&data](sf::Text& itemText, const std::string& title, int fontSize,
		sf::Color color = sf::Color::Transparent) {
				itemText.setString(title);
				itemText.setFont(data.font);
				itemText.setCharacterSize(fontSize);
				if (color != sf::Color::Transparent)
				{
					itemText.setFillColor(color);
				}
		};

		setTextParameters(data.menu.rootItem.hintText, "Apples Game", 48, sf::Color::Red);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 10.f;
		data.menu.rootItem.children.push_back(&data.startGameItem);
		data.menu.rootItem.children.push_back(&data.levelItem);
		data.menu.rootItem.children.push_back(&data.leaderboardItem);
		data.menu.rootItem.children.push_back(&data.settingsItem);
		data.menu.rootItem.children.push_back(&data.exitGameItem);

		setTextParameters(data.startGameItem.text, "Start Game", 24);

		setTextParameters(data.leaderboardItem.text, "Leaderboard", 24);

		setTextParameters(data.levelItem.text, "Difficulty level", 24);

		setTextParameters(data.levelItem.hintText, "Difficulty level", 48, sf::Color::Red);
		data.levelItem.childrenOrientation = Orientation::Vertical;
		data.levelItem.childrenAlignment = Alignment::Middle;
		data.levelItem.childrenSpacing = 10.f;
		data.levelItem.children.push_back(&data.easyItem);
		data.levelItem.children.push_back(&data.easyMiddleItem);
		data.levelItem.children.push_back(&data.middleItem);
		data.levelItem.children.push_back(&data.middleHardItem);
		data.levelItem.children.push_back(&data.hardItem);
		data.levelItem.children.push_back(&data.withoutStoneItem);
		data.levelItem.children.push_back(&data.withStoneItem);
		data.levelItem.children.push_back(&data.someTimeStoneItem);

		setTextParameters(data.settingsItem.text, "Settings", 24);

		setTextParameters(data.settingsItem.hintText, "Settings", 48, sf::Color::Red);
		data.settingsItem.childrenOrientation = Orientation::Vertical;
		data.settingsItem.childrenAlignment = Alignment::Middle;
		data.settingsItem.childrenSpacing = 10.f;
		data.settingsItem.children.push_back(&data.soundItem);
		data.settingsItem.children.push_back(&data.musicItem);

		setTextParameters(data.soundItem.text, "Sound", 24);
		data.soundItem.isChecked = true;
		data.soundItem.checkboxShape.setSize({16.f,16.f});
		data.soundItem.checkboxShape.setOutlineThickness(4.f);
		data.soundItem.checkboxShape.setOutlineColor(sf::Color::White);
		setTextParameters(data.musicItem.text, "Music", 24);
		data.musicItem.isChecked = true;
		data.musicItem.checkboxShape.setSize({ 16.f,16.f });
		data.musicItem.checkboxShape.setOutlineThickness(4.f);
		data.musicItem.checkboxShape.setOutlineColor(sf::Color::White);

		setTextParameters(data.easyItem.text, "Very Easy", 24);
		setTextParameters(data.easyMiddleItem.text, "Easy", 24);
		setTextParameters(data.middleItem.text, "Middle", 24);
		setTextParameters(data.middleHardItem.text, "Hard", 24);
		setTextParameters(data.hardItem.text, "Very Hard", 24);
		setTextParameters(data.withoutStoneItem.text, "Without obstacles", 24);
		setTextParameters(data.withStoneItem.text, "With obstacles", 24);
		setTextParameters(data.someTimeStoneItem.text, "Temporary obstacles", 24);

		setTextParameters(data.exitGameItem.text, "Exit Game", 24);
		setTextParameters(data.exitGameItem.hintText, "Are you sure?", 48, sf::Color::Red);
		data.exitGameItem.childrenOrientation = Orientation::Horizontal;
		data.exitGameItem.childrenAlignment = Alignment::Middle;
		data.exitGameItem.childrenSpacing = 10.f;
		data.exitGameItem.children.push_back(&data.yesItem);
		data.exitGameItem.children.push_back(&data.noItem);

		setTextParameters(data.yesItem.text, "Yes", 24);

		setTextParameters(data.noItem.text, "No", 24);

		InitMenuItem(data.menu.rootItem);
		SelectMenuItem(data.menu, &data.startGameItem);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::B)
			{
				if (static_cast<uint32_t>(game.gameSettings) & static_cast<uint32_t>(GameSettings::sound))
				{
					game.pressButtonSound.play();
				}
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (static_cast<uint32_t>(game.gameSettings) & static_cast<uint32_t>(GameSettings::sound))
				{
					if (!(data.menu.selectedItem == &data.soundItem))
					{
						game.pressButtonSound.play();
					}
				}
				else
				{
					if (data.menu.selectedItem == &data.soundItem)
					{
						game.pressButtonSound.play();
					}
				}
				if (data.menu.selectedItem == &data.startGameItem)
				{
					game.pauseTimeStartGame = PAUSE_TIME_START_GAME;
					SwitchGameState(game, GameStateType::Playing);
				}
				else if (data.menu.selectedItem == &data.leaderboardItem)
				{
					SwitchGameState(game, GameStateType::Leaderboard);
				}
				else if (data.menu.selectedItem == &data.levelItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.easyItem)
				{
					game.gameMode &= ~DIFFICULTY_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::easy);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.easyMiddleItem)
				{
					game.gameMode &= ~DIFFICULTY_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::easyMiddle);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.middleItem)
				{
					game.gameMode &= ~DIFFICULTY_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::middle);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.middleHardItem)
				{
					game.gameMode &= ~DIFFICULTY_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::middleHard);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.hardItem)
				{
					game.gameMode &= ~DIFFICULTY_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::hard);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.withoutStoneItem)
				{
					game.gameMode &= ~STONE_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::withoutStone);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.withStoneItem)
				{
					game.gameMode &= ~STONE_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::withStone);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.someTimeStoneItem)
				{
					game.gameMode &= ~STONE_MASK;
					game.gameMode |= static_cast<uint32_t>(GameSettingBits::someTimeStone);
					//CollapseSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.settingsItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.soundItem)
				{
					data.soundItem.isChecked = !data.soundItem.isChecked;
					game.gameSettings = game.gameSettings ^ static_cast<uint32_t>(GameSettings::sound);
				}
				else if (data.menu.selectedItem == &data.musicItem)
				{
					data.musicItem.isChecked = !data.musicItem.isChecked;
					game.gameSettings = game.gameSettings ^ static_cast<uint32_t>(GameSettings::music);
					if (!(game.gameSettings & static_cast<uint32_t>(GameSettings::music)))
					{
						game.backgroundMusic.stop();
					}
					else
					{
						game.backgroundMusic.play();
					}
				}
				else if (data.menu.selectedItem == &data.exitGameItem)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selectedItem == &data.yesItem)
				{
					SwitchGameState(game, GameStateType::None);
				}
				else if (data.menu.selectedItem == &data.noItem)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
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
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game, float deltaTime)
	{
		
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

		sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
		hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });

		// Checkboxes
		MenuItem* currentContext = GetCurrentMenuContext(data.menu);

		// draw checkboxes if open settings
		if (currentContext == &data.settingsItem)
		{
			for (MenuItem* child : data.settingsItem.children)
			{
				if (!child->isEnabled) continue;

				// get text current position
				sf::Vector2f textPos = child->text.getPosition();

				child->checkboxShape.setPosition(textPos.x + 185.f, textPos.y + 6.f);
				child->checkboxShape.setOutlineColor(sf::Color::White);
				child->checkboxShape.setOutlineThickness(4.f);

				if (child->isChecked)
				{
					child->checkboxShape.setFillColor(sf::Color::Green);
				}
				else
				{
					child->checkboxShape.setFillColor(sf::Color::Transparent);
				}

				window.draw(child->checkboxShape);
			}
		}
	}

}