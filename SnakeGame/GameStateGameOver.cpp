#include "GameStateGameOver.h"
#include <assert.h>
#include "Game.h"

namespace SnakeGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(data.crashSoundBuf.loadFromFile(RESOURCES_PATH + "sounds/Death.wav"));

		data.soundCrash.setBuffer(data.crashSoundBuf);
		data.soundCrash.play();

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

		data.menu.rootItem.children.clear();
		setTextParameters(data.menu.rootItem.hintText, "Enter your Nickname?", 48, sf::Color::White);
		data.menu.rootItem.childrenOrientation = Orientation::Vertical;
		data.menu.rootItem.childrenAlignment = Alignment::Middle;
		data.menu.rootItem.childrenSpacing = 40.f;
		data.menu.rootItem.children.push_back(&data.namePlayerYesItem);
		data.menu.rootItem.children.push_back(&data.namePlayerNoItem);

		setTextParameters(data.namePlayerYesItem.text, "Yes", 32);
		setTextParameters(data.namePlayerNoItem.text, "No", 32);

		setTextParameters(data.mainMenuItem.text, "Main Menu", 24, sf::Color::Black);
		setTextParameters(data.startGameItem.text, "Start Game", 24, sf::Color::Black);

		data.phase = GameOverPhase::Choice;
		data.isInputActive = false;

		setTextParameters(data.scoreTitle, "SCORES", 48, sf::Color::White);
		setTextParameters(data.scoreNumber, FormatNumberWithSpaces(game.lastPlayerScore), 48, sf::Color::White);
		setTextParameters(data.recordsHeader, "Records", 32, sf::Color::White);

		data.startGameItem.checkboxShape.setFillColor(sf::Color::White);
		data.startGameItem.checkboxShape.setSize({ 200.f, 40.f });
		data.startGameItem.checkboxShape.setOutlineThickness(4.f);
		data.startGameItem.checkboxShape.setOutlineColor(sf::Color::White);
		data.mainMenuItem.checkboxShape.setFillColor(sf::Color::White);
		data.mainMenuItem.checkboxShape.setSize({ 200.f, 40.f });
		data.mainMenuItem.checkboxShape.setOutlineThickness(4.f);
		data.mainMenuItem.checkboxShape.setOutlineColor(sf::Color::White);

		RebuildMenuForPhase(data);
	}
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (data.phase == GameOverPhase::Choice || data.phase == GameOverPhase::FinalScreen)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (static_cast<uint32_t>(game.gameSettings) & static_cast<uint32_t>(GameSettings::sound))
					{
						game.pressButtonSound.play();
					}
					if (data.menu.selectedItem == &data.namePlayerNoItem)
					{
						data.phase = GameOverPhase::FinalScreen;
						RebuildMenuForPhase(data);
					}
					else if (data.menu.selectedItem == &data.namePlayerYesItem)
					{
						data.phase = GameOverPhase::InputName;
						data.isInputActive = true;
					}
					else if (data.phase == GameOverPhase::FinalScreen)
					{
						if (data.menu.selectedItem == &data.startGameItem)
						{
							game.pauseTimeStartGame = PAUSE_TIME_START_GAME;
							SwitchGameState(game, GameStateType::Playing);
						}
						else if (data.menu.selectedItem == &data.mainMenuItem)
						{
							SwitchGameState(game, GameStateType::MainMenu);
						}
					}
				}
				else
				{
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

		}
		else if(data.phase == GameOverPhase::InputName && data.isInputActive)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 8)
				{
					if (!data.playerName.empty())
					{
						data.playerName.pop_back();
					}
				}
				else if (event.text.unicode < 128 && isprint(event.text.unicode) && data.playerName.size() < 12)
				{
					data.playerName += static_cast<char>(event.text.unicode);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter && !data.playerName.empty())
				{
					if (static_cast<uint32_t>(game.gameSettings) & static_cast<uint32_t>(GameSettings::sound))
					{
						game.pressButtonSound.play();
					}
					UpdateScore(game.leaderboard, data.playerName, game.lastPlayerScore);
					SerializeGame(game.leaderboard);
					data.phase = GameOverPhase::FinalScreen;
					data.isInputActive = false;
					RebuildMenuForPhase(data);
				}
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float deltaTime)
	{
		if (data.phase == GameOverPhase::InputName && data.isInputActive)
		{
			data.blinkTimer += deltaTime;
			if (data.blinkTimer > 0.5f)
			{
				data.blinkTimer = 0.f;
				data.showCursor = !data.showCursor;
			}
		}
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{

		sf::Vector2f viewSize = (sf::Vector2f)window.getSize();
		
		if (data.phase == GameOverPhase::Choice)
		{
			sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
			hintText->setOrigin(GetItemOrigin(*hintText, { 0.5f, 0.f }));
			hintText->setPosition(viewSize.x / 2.f, 30.f);
			window.draw(*hintText);

			DrawMenu(data.menu, window, { viewSize.x / 2.f, 430.f }, { 0.5f, 0.f });
		}
		else if (data.phase == GameOverPhase::InputName)
		{
			sf::Text prompt("Enter nickname:", data.font, 32);
			prompt.setFillColor(sf::Color::White);
			prompt.setOrigin(GetTextOrigin(prompt, {0.5f, 0.5f}));
			prompt.setPosition(viewSize.x / 2.f, viewSize.y / 2.f - 60.f);
			window.draw(prompt);

			std::string displayName = data.playerName;
			if (data.showCursor)
			{
				displayName += "_";
			}

			sf::Text input(displayName, data.font, 32);
			input.setFillColor(sf::Color::Green);
			input.setOrigin(GetTextOrigin(input, { 0.5f, 0.5f }));
			input.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 20.f);
			window.draw(input);
		}
		else
		{
			data.scoreTitle.setOrigin(GetTextOrigin(data.scoreTitle, { 0.5f, 0.5f }));
			data.scoreTitle.setPosition(viewSize.x / 2.f, 50.f);
			window.draw(data.scoreTitle);

			data.scoreNumber.setOrigin(GetTextOrigin(data.scoreNumber, { 0.5f, 0.5f }));
			data.scoreNumber.setPosition(viewSize.x / 2.f, 100.f);
			window.draw(data.scoreNumber);

			data.recordsHeader.setOrigin(GetTextOrigin(data.recordsHeader, { 0.5f, 0.5f }));
			data.recordsHeader.setPosition(viewSize.x / 2.f, 180.f);
			window.draw(data.recordsHeader);

			float y = 220.f;
			std::vector<Record> sorted = BuildSortedRecords(game.leaderboard);
			for (int i = 0; i < 5 && i < (int)sorted.size(); ++i)
			{
				sf::Text label(std::to_string(i + 1) + ". ", data.font, 28);
				label.setFillColor(sf::Color::White);
				label.setPosition(viewSize.x / 2.f - 190.f, y);
				window.draw(label);

				sf::Text nickname(sorted[i].name, data.font, 28);
				nickname.setOrigin(GetTextOrigin(nickname, {0.5f, 0.f}));
				nickname.setPosition(viewSize.x / 2.f, y);
				window.draw(nickname);

				sf::Text score(FormatNumberWithSpaces(sorted[i].score), data.font, 28);
				score.setOrigin(GetTextOrigin(score, { 1.f, 0.f }));
				score.setPosition(viewSize.x / 2.f + 190.f, y);
				window.draw(score);
				y += 45.f;
			}

			for (MenuItem* child : data.menu.rootItem.children)
			{
				if (!child->isEnabled) continue;

				// get text current position
				sf::Vector2f textPos = child->text.getPosition();

				child->checkboxShape.setPosition(textPos.x - 100.f, textPos.y);
				child->checkboxShape.setOutlineColor(sf::Color::White);
				child->checkboxShape.setOutlineThickness(4.f);

				window.draw(child->checkboxShape);
			}
			data.menu.selectedItem->deselectedColor = sf::Color::Black;
			DrawMenu(data.menu, window, { viewSize.x / 2.f, viewSize.y - 140.f }, { 0.5f, 0.f });
		}
	}

	void RebuildMenuForPhase(GameStateGameOverData& data)
	{
		data.menu.rootItem.children.clear();

		if (data.phase == GameOverPhase::Choice)
		{
			data.menu.rootItem.children.push_back(&data.namePlayerYesItem);
			data.menu.rootItem.children.push_back(&data.namePlayerNoItem);
			SelectMenuItem(data.menu, &data.namePlayerNoItem);
		}
		else if (data.phase == GameOverPhase::FinalScreen)
		{
			data.menu.rootItem.children.push_back(&data.startGameItem);
			data.menu.rootItem.children.push_back(&data.mainMenuItem);
			SelectMenuItem(data.menu, &data.startGameItem);
		}
		InitMenuItem(data.menu.rootItem);
	}
}