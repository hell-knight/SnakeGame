#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include <assert.h>

namespace ArkanoidGame
{
	GameState::GameState(GameStateType t) 
		: type(t)
	{
		InitData();
	}

	GameState::GameState(GameState&& other) noexcept
		: type(other.type)
		, data(other.data)
		, isExclusivelyVisible(other.isExclusivelyVisible)
	{
		other.type = GameStateType::None;
		other.data = nullptr;
		other.isExclusivelyVisible = false;
	}

	GameState::~GameState()
	{
		ShutdownData();
	}

	GameState& GameState::operator=(GameState&& other) noexcept
	{
		if (this != &other)
		{
			ShutdownData();

			type = other.type;
			data = other.data;
			isExclusivelyVisible = other.isExclusivelyVisible;

			other.type = GameStateType::None;
			other.data = nullptr;
			other.isExclusivelyVisible = false;
		}
		return *this;
	}

	void GameState::InitData()
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			InitGameStateMainMenu(*(GameStateMainMenuData*)data);
			break;
		}
		case GameStateType::Playing:
		{
			data = new GameStatePlayingData();
			InitGameStatePlaying(*(GameStatePlayingData*)data);
			break;
		}
		case GameStateType::GameOver:
		{
			data = new GameStateGameOverData();
			InitGameStateGameOver(*(GameStateGameOverData*)data);
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = new GameStatePauseMenuData();
			InitGameStatePauseMenu(*(GameStatePauseMenuData*)data);
			break;
		}
		case GameStateType::Records:
		{
			data = new GameStateRecordsData();
			InitGameStateRecords(*(GameStateRecordsData*)data);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::ShutdownData()
	{
		if (data == nullptr)
		{
			return;
		}

		switch (type)
		{
		case GameStateType::MainMenu:
		{
			ShutdownGameStateMainMenu(*(GameStateMainMenuData*)data);
			delete (GameStateMainMenuData*)data;
			break;
		}
		case GameStateType::Playing:
		{
			ShutdownGameStatePlaying(*(GameStatePlayingData*)data);
			delete (GameStatePlayingData*)data;
			break;
		}
		case GameStateType::GameOver:
		{
			ShutdownGameStateGameOver(*(GameStateGameOverData*)data);
			delete (GameStateGameOverData*)data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			ShutdownGameStatePauseMenu(*(GameStatePauseMenuData*)data);
			delete (GameStatePauseMenuData*)data;
			break;
		}
		case GameStateType::Records:
		{
			ShutdownGameStateRecords(*(GameStateRecordsData*)data);
			delete (GameStateRecordsData*)data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}

		data = nullptr;
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData*)data, event);
			break;
		}
		case GameStateType::Playing:
		{
			HandleGameStatePlayingWindowEvent(*(GameStatePlayingData*)data, event);
			break;
		}
		case GameStateType::GameOver:
		{
			HandleGameStateGameOverWindowEvent(*(GameStateGameOverData*)data, event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			HandleGameStatePauseMenuWindowEvent(*(GameStatePauseMenuData*)data, event);
			break;
		}
		case GameStateType::Records:
		{
			HandleGameStateRecordsWindowEvent(*(GameStateRecordsData*)data, event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::Update(float timeDelta)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			UpdateGameStateMainMenu(*(GameStateMainMenuData*)data, timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			UpdateGameStatePlaying(*(GameStatePlayingData*)data, timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			UpdateGameStateGameOver(*(GameStateGameOverData*)data, timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
		{
			UpdateGameStatePauseMenu(*(GameStatePauseMenuData*)data, timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			UpdateGameStateRecords(*(GameStateRecordsData*)data, timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			DrawGameStateMainMenu(*(GameStateMainMenuData*)data, window);
			break;
		}
		case GameStateType::Playing:
		{
			DrawGameStatePlaying(*(GameStatePlayingData*)data, window);
			break;
		}
		case GameStateType::GameOver:
		{
			DrawGameStateGameOver(*(GameStateGameOverData*)data, window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			DrawGameStatePauseMenu(*(GameStatePauseMenuData*)data, window);
			break;
		}
		case GameStateType::Records:
		{
			DrawGameStateRecords(*(GameStateRecordsData*)data, window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
}