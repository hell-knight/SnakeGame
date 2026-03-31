#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>
#include <iostream>

namespace SnakeGame
{
	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init game resources (terminate if error)
		assert(data.player.playerBodyBottomLeftTexture.loadFromFile(RESOURCES_PATH + "\\body_bottomleft.png"));
		assert(data.player.playerBodyBottomRightTexture.loadFromFile(RESOURCES_PATH + "\\body_bottomright.png"));
		assert(data.player.playerBodyTopLeftTexture.loadFromFile(RESOURCES_PATH + "\\body_topleft.png"));
		assert(data.player.playerBodyTopRightTexture.loadFromFile(RESOURCES_PATH + "\\body_topright.png"));
		assert(data.player.playerBodyHorizontalTexture.loadFromFile(RESOURCES_PATH + "\\body_horizontal.png"));
		assert(data.player.playerBodyVerticalTexture.loadFromFile(RESOURCES_PATH + "\\body_vertical.png"));
		assert(data.player.playerHeadDownTexture.loadFromFile(RESOURCES_PATH + "\\head_down.png"));
		assert(data.player.playerHeadLeftTexture.loadFromFile(RESOURCES_PATH + "\\head_left.png"));
		assert(data.player.playerHeadRightTexture.loadFromFile(RESOURCES_PATH + "\\head_right.png"));
		assert(data.player.playerHeadUpTexture.loadFromFile(RESOURCES_PATH + "\\head_up.png"));
		assert(data.player.playerTailDownTexture.loadFromFile(RESOURCES_PATH + "\\tail_down.png"));
		assert(data.player.playerTailLeftTexture.loadFromFile(RESOURCES_PATH + "\\tail_left.png"));
		assert(data.player.playerTailRightTexture.loadFromFile(RESOURCES_PATH + "\\tail_right.png"));
		assert(data.player.playerTailUpTexture.loadFromFile(RESOURCES_PATH + "\\tail_up.png"));
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "\\appleSnake.png"));
		assert(data.stoneTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(data.player.eatenSoundBuf.loadFromFile(RESOURCES_PATH + "\\sounds\\AppleEat.wav"));
		assert(data.player.wallSoundBuf.loadFromFile(RESOURCES_PATH + "\\sounds\\sound_collision.wav"));
		assert(data.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Black.ttf"));
		assert(data.player.snakeTurnBuf.loadFromFile(RESOURCES_PATH + "\\sounds\\turn_snake.wav"));
		assert(data.player.startGameBuf.loadFromFile(RESOURCES_PATH + "\\sounds\\start_game.wav"));

		LoadAnimatedSprite(data.player.animExplosion, {
			RESOURCES_PATH + "\\explosion\\frame_00_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_01_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_02_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_03_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_04_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_05_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_06_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_07_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_08_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_09_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_10_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_11_delay-0.1s.png",
			RESOURCES_PATH + "\\explosion\\frame_12_delay-0.1s.png",
			});

		SetFrameTime(data.player.animExplosion, 0.1f);

		// Init grid
		InitGrid(data.grid);

		// Init wall
		InitWall(data.wall, data.gameOffsetY);

		// Init player
		InitSnake(data.player);

		// Init apple
		InitApples(data.apple, data.appleTexture);
		SpawnApple(data.grid, data.apple);

		InitGameModeSettings(data, game.gameMode);
	
		data.score = 0;

		data.topPanel.setSize({ SCREEN_WIDTH, data.gameOffsetY });
		data.topPanel.setFillColor(sf::Color(30, 30, 30));
		data.topPanel.setOutlineThickness(4.f);
		data.topPanel.setOutlineColor(sf::Color(100, 100, 100));

		data.scoreText.setFont(data.font);
		data.scoreText.setCharacterSize(24);
		data.scoreText.setFillColor(sf::Color::Yellow);
		data.scoreText.setPosition(SCREEN_WIDTH - 150.f, 15.f);

		data.deathTimer = 0.f;
		data.isDying = false;

		data.poisonTimer = 0.f;
		data.disorientTimer = 0.f;

		data.player.startGameSound.play();
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				if (static_cast<uint32_t>(game.gameSettings) & static_cast<uint32_t>(GameSettings::sound))
				{
					game.pressButtonSound.play();
				}
				PushGameState(game, GameStateType::PauseGame, false);
			}
		}
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float deltaTime)
	{
		HandleInput(data);

		if (data.isDying)
		{
			data.deathTimer -= deltaTime;
			UpdateAnimatedSprite(data.player.animExplosion);
			if (data.deathTimer <= 0)
			{
				// Find player in records table and update his score
				game.lastPlayerScore = data.score;
				SwitchGameState(game, GameStateType::GameOver);
			}
		}
		else
		{

			if (game.pauseTimeStartGame > 0.f)
			{
				game.pauseTimeStartGame -= deltaTime;
			}
			else
			{
				if ((game.gameMode & STONE_MASK) == static_cast<uint32_t>(GameSettingBits::someTimeStone))
				{
					for (size_t i = 0; i < data.stones.size(); ++i)
					{
						data.stones[i].lifetime -= deltaTime;
						if (data.stones[i].lifetime <= 0.f)
						{
							SetCell(data.grid, data.stones[i].position.x, data.stones[i].position.y, CellType::Empty);
							data.stones.erase(data.stones.begin() + i);
							continue;
						}
					}
				}

				// Editing effect timers
				if (data.poisonTimer > 0.f)
				{
					data.poisonTimer -= deltaTime;
				}
				if (data.disorientTimer > 0.f)
				{
					data.disorientTimer -= deltaTime;
				}

				// Reducing the shelf life of special apples
				if (data.apple.lifetime > 0.f && data.apple.type != AppleType::Normal)
				{
					data.apple.lifetime -= deltaTime;
					if (data.apple.lifetime <= 0.f)
					{
						// The apple is gone
						SetCell(data.grid, data.apple.position.x, data.apple.position.y, CellType::Empty);
						SpawnApple(data.grid, data.apple);
					}
				}

				data.moveTimer += deltaTime;

				// How many seconds does it take per cell
				const float moveInterval = CELL_SIZE / data.player.speed;

				if (data.moveTimer >= moveInterval)
				{
					data.moveTimer -= moveInterval;

					if (!MoveSnake(data.player, data.grid))
					{
						// collision
						data.player.wallCollisionSound.play();
						data.isDying = true;
						data.deathTimer = DEATH_DELAY;
						return;
					}

					// if grow apple
					if (data.player.body[0].position.x == data.apple.position.x &&
						data.player.body[0].position.y == data.apple.position.y)
					{
						if (data.apple.type == AppleType::Big)
						{
							data.score += BIG_APPLE_POINT;
						}
						else if (data.apple.type == AppleType::Poisoned)
						{
							data.poisonTimer = POISONED_EFFECT_DURATION;
							data.player.speed *= POISONED_SPEED_MULTIPLIER;
						}
						else if (data.apple.type == AppleType::Disorienting)
						{
							data.disorientTimer = DISORIENT_DURATION;
						}
						data.player.grow = true;
						SpawnApple(data.grid, data.apple);
						data.player.soundEat.play();
						data.score += data.pointLevel;
						data.player.lengthSnake++;

						if ((game.gameMode & STONE_MASK) == static_cast<uint32_t>(GameSettingBits::someTimeStone))
						{
							SpawnTemporaryStone(data, data.grid);
						}
					}

					// if don't grow, cut off the tail
					if (!data.player.grow)
					{
						int tailX = data.player.body.back().position.x;
						int tailY = data.player.body.back().position.y;
						SetCell(data.grid, tailX, tailY, CellType::Empty);
						data.player.body.pop_back();
						CellType newTail = IdentityTypeCellTail(data.player.body.back().position,
							data.player.body[data.player.body.size() - 2].position);
						SetCell(data.grid, data.player.body.back().position.x, data.player.body.back().position.y, newTail);
						InsertSprite(data.player, data.player.body.back(), newTail);
					}
					else
					{
						data.player.grow = false;
					}

					// Restoring Normal Speed After Poisoning
					if (data.poisonTimer <= 0.f && data.player.speed != data.currentSpeed)
					{
						data.player.speed = data.currentSpeed;
					}
				}
			}
		}
		data.scoreText.setString("Scores: " + std::to_string(data.score));
	}

	void HandleInput(GameStatePlayingData& data)
	{
		bool reversed = data.disorientTimer > 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (ChangeDirection(data.player, reversed ? PlayerDirection::Left : PlayerDirection::Right))
			{
				data.player.snakeTurnSound.play();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (ChangeDirection(data.player, reversed ? PlayerDirection::Down : PlayerDirection::Up))
			{
				data.player.snakeTurnSound.play();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (ChangeDirection(data.player, reversed ? PlayerDirection::Right : PlayerDirection::Left))
			{
				data.player.snakeTurnSound.play();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (ChangeDirection(data.player, reversed ? PlayerDirection::Up : PlayerDirection::Down))
			{
				data.player.snakeTurnSound.play();
			}
		}
	}

	void InitGameModeSettings(GameStatePlayingData& data, const uint32_t gameMode)
	{
		uint32_t difficulty = gameMode & DIFFICULTY_MASK;

		switch(difficulty)
		{
		case static_cast<uint32_t>(GameSettingBits::easy):
			data.player.speed = SPEED_VERY_EASY;
			data.pointLevel = LEVEL_COEFFICIENT_ONE;
			break;
		case static_cast<uint32_t>(GameSettingBits::easyMiddle):
			data.player.speed = SPEED_EASY;
			data.pointLevel = LEVEL_COEFFICIENT_TWO;
			break;
		case static_cast<uint32_t>(GameSettingBits::middle):
			data.player.speed = SPEED_MIDDLE;
			data.pointLevel = LEVEL_COEFFICIENT_THREE;
			break;
		case static_cast<uint32_t>(GameSettingBits::middleHard):
			data.player.speed = SPEED_HARD;
			data.pointLevel = LEVEL_COEFFICIENT_FOUR;
			break;
		case static_cast<uint32_t>(GameSettingBits::hard):
			data.player.speed = SPEED_VERY_HARD;
			data.pointLevel = LEVEL_COEFFICIENT_FIVE;
			break;
		}
		data.currentSpeed = data.player.speed;

		uint32_t stoneMode = gameMode & STONE_MASK;
		data.stones.clear();
		if (stoneMode == static_cast<uint32_t>(GameSettingBits::withStone))
		{
			// Init stones
			
			data.pointLevel += WITH_STONE_POINT;
			data.stones.resize(NUM_STONES);
			for (auto& stone : data.stones)
			{
				InitStone(stone, data.stoneTexture);
				stone.position = SpawnStone(data.grid);
			}
			
		}
		else if (stoneMode == static_cast<uint32_t>(GameSettingBits::someTimeStone))
		{
			data.pointLevel += SOMETIME_STONE_POINT;
		}
		else if (stoneMode == static_cast<uint32_t>(GameSettingBits::withoutStone))
		{
			data.pointLevel += WITHOUT_STONE_POINT;
		}
	}

	void SpawnTemporaryStone(GameStatePlayingData& data, Grid& grid)
	{
		// chance spawn
		if (static_cast<float>(rand()) / RAND_MAX > TEMPORARY_STONE_SPAWN_CHANCE)
		{
			return;
		}

		Stone newStone;
		InitStone(newStone, data.stoneTexture);
		newStone.position = SpawnStone(grid);
		newStone.lifetime = TEMPORARY_STONE_LIFETIME;
		data.stones.push_back(newStone);
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		window.draw(data.topPanel);
		window.draw(data.scoreText);
		if (!(game.gameStateStack.back().type == GameStateType::PauseGame))
		{
			for (auto& seg : data.player.body)
			{
				DrawSnakeSegment(seg, window, data.gameOffsetY);
			}

			DrawApple(data.apple, window, data.gameOffsetY);

			DrawWall(data.wall, window);

			for (auto& seg : data.stones)
			{
				DrawStone(seg, window, TOP_PANEL_SIZE);
			}
		}
		if (data.isDying)
		{
			SetSpriteSize(data.player.animExplosion.sprite, 2 * CELL_SIZE, 2 * CELL_SIZE);
			SetSpriteRelativeOrigin(data.player.animExplosion.sprite, 0.5f, 0.5f);
			data.player.animExplosion.sprite.setPosition(data.player.body[0].sprite.getPosition());
			DrawAnimatedSprite(data.player.animExplosion, window);
		}
	}
}