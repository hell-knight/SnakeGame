#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "Block.h"
#include "DurableBlock.h"
#include "GlassBlock.h"
#include "ThreeHitBlock.h"

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));

		// factoriesInit
		factories.emplace(BlockType::Simple, std::make_unique<SimpleBlockFactory>());
		factories.emplace(BlockType::ThreeHit, std::make_unique<ThreeHitBlockFactory>());
		factories.emplace(BlockType::Unbreackable, std::make_unique<UnbreackableBlockFactory>());
		//factories.emplace(BlockType::Glass, std::make_unique<GlassBlockFactory>());

		// Init background
		background.setSize(sf::Vector2f((float)SETTINGS.SCREEN_WIDTH, (float)SETTINGS.SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setString("Score: " + std::to_string(score));
		score = 0;

		livesText.setFont(font);
		livesText.setCharacterSize(24);
		livesText.setFillColor(sf::Color::Red);
		lives = 3;

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		//gameObjects.clear();
		gameObjects.emplace_back(std::make_shared<Platform>(
			sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT / 2.f})));
		auto ball = (std::make_shared<Ball>(
			sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT - SETTINGS.BALL_SIZE / 2.f })));
		ball->AddObserver(weak_from_this());
		gameObjects.emplace_back(ball);

		createBlocks();
		SaveState();

		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		static auto updateFunctor = [timeDelta](auto obj) {obj->Update(timeDelta); };

		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunctor);
		std::for_each(blocks.begin(), blocks.end(), updateFunctor);

		std::shared_ptr<Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);

		auto isCollision = platform->CheckCollision(ball);

		bool needInverseDirX = false;
		bool needInverseDirY = false;
		bool hasBrokeOneBlock = false;
		// remove-erase idiom
		//blocks.erase(
		//	std::remove_if(blocks.begin(), blocks.end(),
		//		[ball, &hasBrokeOneBlock, &needInverseDirX, &needInverseDirY, this](auto block) -> bool {
		//			if (!block) { return true; }

		//			bool collided = block->CheckCollision(ball);
		//			if (collided)
		//			{
		//				//score += block->GetPoints();
		//				SaveState();
		//				// Rebound applies only to standard blocks
		//				if ((!hasBrokeOneBlock) && block->AffectsBallDirection())
		//				{
		//					hasBrokeOneBlock = true;
		//					const auto ballPos = ball->GetPosition();
		//					const auto blockRect = block->GetRect();

		//					GetBallInverse(ballPos, blockRect, needInverseDirX, needInverseDirY);
		//				}
		//			}
		//			return block->IsBroken();
		//		}),
		//	blocks.end()
		//);

		std::vector<std::shared_ptr<Block>> blocksToRemove;

		for (auto& block : blocks)
		{
			if (!block) continue;

			bool collided = block->CheckCollision(ball);
			if (collided)
			{
				SaveState();
				// Rebound applies only to standard blocks
				if ((!hasBrokeOneBlock) && block->AffectsBallDirection())
				{
					hasBrokeOneBlock = true;
					const auto ballPos = ball->GetPosition();
					const auto blockRect = block->GetRect();

					GetBallInverse(ballPos, blockRect, needInverseDirX, needInverseDirY);
				}
			}

			if (block->IsBroken())
			{
				blocksToRemove.push_back(block);
			}
		}

		for (const auto& toRemove : blocksToRemove)
		{
			auto it = std::find(blocks.begin(), blocks.end(), toRemove);
			if (it != blocks.end())
			{
				blocks.erase(it);
			}
		}

		if (needInverseDirX)
		{
			ball->InvertDirectionX();
		}

		if (needInverseDirY)
		{
			ball->InvertDirectionY();
		}

		scoreText.setString("Score: " + std::to_string(score));
		livesText.setString("Lives: " + std::to_string(lives));
		//SaveState();
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		static auto drawFunc = [&window](auto block) {block->Draw(window); };
		// Draw game objects
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(blocks.begin(), blocks.end(), drawFunc);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		livesText.setOrigin(GetTextOrigin(livesText, { 0.f, 0.f }));
		livesText.setPosition(10.f, 40.f);
		window.draw(livesText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::LoadNextLevel()
	{
		if (currentLevel >= levelLoader.GetLevelCount() - 1)
		{
			Game& game = Application::Instance().GetGame();
			
			game.WinGame(SETTINGS.PLAYER_NAME, score);
		}
		else
		{
			std::shared_ptr<Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
			std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
			platform->restart();
			ball->restart();

			blocks.clear();
			++currentLevel;
			createBlocks();
			SaveState();
		}
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		if (auto block = std::dynamic_pointer_cast<Block>(observable); block)
		{
		
			--breackableBlocksCount;
			score += block->GetPoints();
			Game& game = Application::Instance().GetGame();
			if (breackableBlocksCount == 0)
			{
				game.LoadNextLevel();
			}
		}
		else if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
		{
			if (ball->GetPosition().y > gameObjects.front()->GetRect().top)
			{
				if (lives > 1)
				{
					--lives;
					//SaveState();
					LoadLastState();
					auto platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
					auto ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
					platform->restart();
					ball->restart();
				}
				else
				{
					gameOverSound.play();
					Application::Instance().GetGame().LooseGame(SETTINGS.PLAYER_NAME, score);
				}
			}
		}
	}

	std::unique_ptr<Memento> GameStatePlayingData::CreateMemento() const
	{
		return std::make_unique<Memento>(score, currentLevel, breackableBlocksCount, blocks);
	}

	void GameStatePlayingData::SetMemento(const Memento& memento)
	{
		score = memento.GetScore();
		currentLevel = memento.GetCurrentLevel();
		breackableBlocksCount = memento.GetBreackableBlocksCount();
		blocks = memento.GetBlocks();
	}

	void GameStatePlayingData::SaveState()
	{
		lastMemento = CreateMemento();
	}

	void GameStatePlayingData::LoadLastState()
	{
		if (lastMemento)
		{
			SetMemento(*lastMemento);
		}
	}

	void GameStatePlayingData::createBlocks()
	{
		for (const auto& pair : factories)
		{
			pair.second->ClearCounter();
		}
		auto self = weak_from_this();

		auto level = levelLoader.GetLevel(currentLevel);
		for (auto pairPosBlockType : level.m_blocks)
		{
			auto blockType = pairPosBlockType.second;
			sf::Vector2i pos = pairPosBlockType.first;

			sf::Vector2f position{
					(float)(SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + pos.x * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT))
					, (float)pos.y * SETTINGS.BLOCK_HEIGHT };

			blocks.emplace_back(factories.at(blockType)->CreateBlock(position));
			blocks.back()->AddObserver(self);
		}

		for (const auto& pair : factories)
		{
			breackableBlocksCount += pair.second->GetcreatedBreackableBlocksCount();
		}
	}

	void GameStatePlayingData::GetBallInverse(const sf::Vector2f ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY)
	{
		if (ballPos.y > blockRect.top + blockRect.height)
		{
			needInverseDirY = true;
		}
		if (ballPos.x < blockRect.left)
		{
			needInverseDirX = true;
		}
		if (ballPos.x > blockRect.left + blockRect.width)
		{
			needInverseDirX = true;
		}
	}

}
