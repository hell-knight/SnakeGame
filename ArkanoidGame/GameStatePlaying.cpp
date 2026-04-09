#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);
		score = 0;

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		//gameObjects.clear();
		gameObjects.emplace_back(std::make_shared<Platform>());
		gameObjects.emplace_back(std::make_shared<Ball>());

		for (int i = 0; i < BLOCK_COLS; ++i)
		{
			for (int j = 0; j < BLOCK_ROWS; ++j)
			{
				auto block = std::make_shared<Block>();
				gameObjects.emplace_back(block);
				block->Init();
				float x = BLOCK_START_X + i * (BLOCK_WIDTH + BLOCK_SPACING);
				float y = BLOCK_START_Y + j * (BLOCK_HEIGHT + BLOCK_SPACING);
				block->SetPosition({x, y});
			}
		}

		gameObjects[0]->Init();
		gameObjects[1]->Init();

		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		for (auto&& object : gameObjects)
		{
			object->Update(timeDelta);
		}

		const Platform* platform = (Platform*)gameObjects[0].get();
		Ball* ball = (Ball*)gameObjects[1].get();

		bool isCollision = platform->CheckCollisionWithBall(*ball);
		if (isCollision)
		{
			ball->ReboundFromPlatform();
		}
		
		for (size_t i = 2; i < gameObjects.size(); ++i)
		{
			Block* block = (Block*)gameObjects[i].get();
				if (block->CheckCollisionWithBall(*ball))
				{
					ball->ReboundFromBlock(*block);
					score += GAME_POINT;
					scoreText.setString("Score: " + std::to_string(score));
					std::swap(gameObjects[i], gameObjects.back());
					gameObjects.pop_back();
					--i;
				}
		}
		
		const bool isGameFinished = !isCollision && ball->GetPosition().y > platform->GetRect().top;
		const bool isGameWin = gameObjects.size() == 2;
		Game& game = Application::Instance().GetGame();
		if (isGameWin)
		{
			game.PushState(GameStateType::Win, false);
		}
		else if (isGameFinished)
		{
			gameOverSound.play();

			// Find player in records table and update his score
			game.PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw game objects
		for (auto&& object : gameObjects)
		{
			object->Draw(window);
		}

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
