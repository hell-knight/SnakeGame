#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	class GameState
	{
	public:
		explicit GameState(GameStateType t = GameStateType::None);
		GameState(const GameState&) = delete;
		GameState(GameState&& other) noexcept;
		~GameState();

		GameState& operator=(const GameState&) = delete;
		GameState& operator=(GameState&& other) noexcept;

		GameStateType GetType() const { return type; }
		void* GetData() { return data; }
		const void* GetData() const { return data; }
		bool IsExclusivelyVisible() const { return isExclusivelyVisible; }

		void SetExclusivelyVisible(bool value) { isExclusivelyVisible = value; }

		void HandleWindowEvent(sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		void InitData();
		void ShutdownData();

		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};
}