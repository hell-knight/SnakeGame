#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Wall.h"
#include "Leaderboard.h"
#include "AnimatedSprite.h"
#include "Stone.h"

namespace SnakeGame
{
	struct GameStatePlayingData;

	enum class GameSettingBits
	{
		easy = 1 << 0,
		easyMiddle = 1 << 1,
		middle = 1 << 2,
		middleHard = 1 << 3,
		hard = 1 << 4,
		withoutStone = 1 << 5,
		withStone = 1 << 6,
		someTimeStone = 1 << 7,

		Default = easy | withoutStone,
		Empty = 0
	};

	// Masks for mutually exclusive groups
	constexpr uint32_t DIFFICULTY_MASK =
		static_cast<uint32_t>(GameSettingBits::easy) |
		static_cast<uint32_t>(GameSettingBits::easyMiddle) |
		static_cast<uint32_t>(GameSettingBits::middle) |
		static_cast<uint32_t>(GameSettingBits::middleHard) |
		static_cast<uint32_t>(GameSettingBits::hard);

	constexpr uint32_t STONE_MASK =
		static_cast<uint32_t>(GameSettingBits::withoutStone) |
		static_cast<uint32_t>(GameSettingBits::withStone) |
		static_cast<uint32_t>(GameSettingBits::someTimeStone);

	enum class GameSettings
	{
		sound = 1 << 0,
		music = 1 << 1,

		Default = sound | music,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Leaderboard,
		Playing,
		PauseGame,
		GameOver,
		ExitDialog
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	struct Game
	{
		// global game data
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;
		float pauseTimeStartGame = 0.f;
		int lastPlayerScore = 0;

		sf::SoundBuffer pressButtonBuf;
		sf::Sound pressButtonSound;
		sf::Music backgroundMusic;
		
		uint32_t gameMode = static_cast<uint32_t>(GameSettingBits::Default);
		uint32_t gameSettings = static_cast<uint32_t>(GameSettings::Default);
		std::map<std::string, int> leaderboard;
	};

	void RestartGame(Game& game);
	void InitGame(Game& game);
	bool UpdateGame(Game& game, float deltaTime);	// Return false if game should be closed
	void DrawGame(Game& game, sf::RenderWindow& window);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	// Add new game state on top of the stack
	void PushGameState(Game& game, GameStateType stateType, bool isExclusivelyVisible);

	// Remove current game state from the stack
	void PopGameState(Game& game);

	// Remove all game states from the stack and add new one
	void SwitchGameState(Game& game, GameStateType newState);
	
	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, GameState& state, float deltaTime);
	void DrawGameState(Game& game, GameState& state, sf::RenderWindow& window);
}