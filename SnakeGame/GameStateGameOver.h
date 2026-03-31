#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Constants.h"

namespace SnakeGame
{
	struct Game;

	enum class GameOverPhase
	{
		Choice,		// choice yes or no enter nickname
		InputName,
		FinalScreen	// final gameover
	};

	struct GameStateGameOverData
	{
		// Recources
		sf::Font font;
		sf::Sound soundCrash;
		sf::SoundBuffer crashSoundBuf;

		GameOverPhase phase = GameOverPhase::Choice;

		MenuItem startGameItem;
		MenuItem mainMenuItem;
		MenuItem namePlayerYesItem;
		MenuItem namePlayerNoItem;
		MenuItem enterNicknameItem;
		MenuItem nameInputItem;
		Menu menu;
		// UI data
		sf::Text scoreTitle;
		sf::Text scoreNumber;
		sf::Text recordsHeader;
		std::vector<sf::Text> recordsLabel;
		std::vector<sf::Text> recordsScore;

		// window enter nickname
		bool isInputActive = false;
		std::string playerName = STANDART_PLAYER_NAME;
		float blinkTimer = 0.f;
		bool showCursor = true;
	};
	
	// Returns pointer to the allocated data
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game, float deltaTime);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
	void RebuildMenuForPhase(GameStateGameOverData& data);
}