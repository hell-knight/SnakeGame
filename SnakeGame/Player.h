#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"
#include "GridGame.h"
#include "AnimatedSprite.h"

namespace SnakeGame
{
	enum class PlayerDirection
	{
		None = 0,
		Right,
		Up,
		Left,
		Down
	};

	struct SnakeSegment
	{
		Position2I position;
		sf::Sprite sprite;
	};

	struct Player
	{
		std::vector<SnakeSegment> body;	// body snake (head - body[0])
		bool grow = false;	// flag grow (after apple)
		float speed = SPEED_VERY_EASY;
		int lengthSnake = START_LENGHT_SNAKE;
		PlayerDirection direction = PlayerDirection::Right;
		sf::Sound soundEat;
		sf::SoundBuffer eatenSoundBuf;
		sf::SoundBuffer wallSoundBuf;
		sf::SoundBuffer snakeTurnBuf;
		sf::SoundBuffer startGameBuf;
		sf::Sound startGameSound;
		sf::Sound snakeTurnSound;
		sf::Sound wallCollisionSound;
		sf::Texture playerHeadLeftTexture;
		sf::Texture playerHeadRightTexture;
		sf::Texture playerHeadDownTexture;
		sf::Texture playerHeadUpTexture;
		sf::Texture playerBodyVerticalTexture;
		sf::Texture playerBodyHorizontalTexture;
		sf::Texture playerBodyBottomLeftTexture;
		sf::Texture playerBodyBottomRightTexture;
		sf::Texture playerBodyTopRightTexture;
		sf::Texture playerBodyTopLeftTexture;
		sf::Texture playerTailUpTexture;
		sf::Texture playerTailDownTexture;
		sf::Texture playerTailLeftTexture;
		sf::Texture playerTailRightTexture;

		AnimatedSprite animExplosion;
	};

	struct Game;
	struct Grid;
	
	void InitSnake(Player& player);
	bool MoveSnake(Player& player, Grid& grid);
	bool ChangeDirection(Player& player, PlayerDirection newDirection);
	void InsertSprite(Player& player, SnakeSegment& seg, CellType type);
	void DrawSnakeSegment(SnakeSegment& seg, sf::RenderWindow& window, float topPanelHeight);
}