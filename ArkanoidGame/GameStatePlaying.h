#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "GameStateData.h"
#include "LevelLoader.h"
#include "BlockFactory.h"
#include <unordered_map>
#include "IObserver.h"
#include "Memento.h"

namespace ArkanoidGame
{
	class Game;
	class Block;
	class BlockFactory;

	class GameStatePlayingData : public GameStateData, public IObserver, public
		std::enable_shared_from_this<GameStatePlayingData>
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;

		std::unique_ptr<Memento> CreateMemento() const;
		void SetMemento(const Memento& memento);
		void SaveState();
		void LoadLastState();

	private:
		void createBlocks();
		void GetBallInverse(const sf::Vector2f ballPos, const sf::FloatRect& blockRect,
			bool& needInverseDirX, bool& needInverseDirY);

		// Resources
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;
		int score = 0;
		int lives = 3;

		// Memento
		std::unique_ptr<Memento> lastMemento;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text livesText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;

		// Blocks creator
		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> factories;
		int breackableBlocksCount = 0;

		// Levels
		LevelLoader levelLoader;
		int currentLevel = 0;
	};
}
