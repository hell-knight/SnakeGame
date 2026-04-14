#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "GameStateData.h"
#include "LevelLoader.h"
#include "BlockFactory.h"
#include <unordered_map>

namespace ArkanoidGame
{
	class Game;
	class Block;
	class BlockFactory;

	class GameStatePlayingData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void LoadNextLevel();

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

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;

		// Blocks creator
		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> factories;
		int unbreackableBlocksCount = 0;

		// Levels
		LevelLoader levelLoader;
		int currentLevel = 0;
	};
}
