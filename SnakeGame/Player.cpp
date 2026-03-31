#include "Player.h"
#include "Game.h"
#include "GridGame.h"

namespace SnakeGame
{
	void InitSnake(Player& player)
	{
		player.body.clear();
		player.direction = PlayerDirection::Right;
		player.grow = false;

		// init player sprite
		for (int i = 0; i < player.lengthSnake; ++i)
		{
			player.body.push_back({ GRID_SIZE / 2 - i, GRID_SIZE / 2 });
			if (i == 0)
			{
				player.body[i].sprite.setTexture(player.playerHeadRightTexture);
			}
			else if (i == (player.lengthSnake - 1))
			{
				player.body[i].sprite.setTexture(player.playerTailLeftTexture);
			}
			else
			{
				player.body[i].sprite.setTexture(player.playerBodyHorizontalTexture);
			}
			SetSpriteSize(player.body[i].sprite, PLAYER_SIZE, PLAYER_SIZE);
			SetSpriteRelativeOrigin(player.body[i].sprite, 0.5f, 0.5f);
		}

		// init player sound
		player.soundEat.setBuffer(player.eatenSoundBuf);
		player.wallCollisionSound.setBuffer(player.wallSoundBuf);
		player.snakeTurnSound.setBuffer(player.snakeTurnBuf);
		player.startGameSound.setBuffer(player.startGameBuf);
	}

	bool MoveSnake(Player& player, Grid& grid)
	{
		if (player.direction == PlayerDirection::None)
		{
			return true;
		}

		int newCellX = player.body[0].position.x;
		int newCellY = player.body[0].position.y;

		switch (player.direction)
		{
			case PlayerDirection::Up:		--newCellY; break;
			case PlayerDirection::Down:		++newCellY; break;
			case PlayerDirection::Left:		--newCellX; break;
			case PlayerDirection::Right:	++newCellX; break;
		}

		if (!IsCellFree(grid, newCellX, newCellY) && grid.cells[newCellX][newCellY] != CellType::Apple)
		{
			player.wallCollisionSound.play();
			return false;
		}

		// add new head
		CellType replaceHead = ReplaceTypeCellHead(player.body[0].position, player.body[1].position, { newCellX, newCellY });
		SetCell(grid, player.body[0].position.x, player.body[0].position.y, replaceHead);
		InsertSprite(player, player.body[0], replaceHead);
		SnakeSegment newHead = { newCellX , newCellY };
		CellType newHeadTypeCell = IdentityTypeCellHead(player);
		SetCell(grid, newCellX, newCellY, newHeadTypeCell);
		InsertSprite(player, newHead, newHeadTypeCell);
		player.body.insert(player.body.begin(), newHead);

		return true;
	}

	bool ChangeDirection(Player& player, PlayerDirection newDirection)
	{
		if ((player.direction == PlayerDirection::Up && newDirection == PlayerDirection::Down) ||
			(player.direction == PlayerDirection::Down && newDirection == PlayerDirection::Up) ||
			(player.direction == PlayerDirection::Left && newDirection == PlayerDirection::Right) ||
			(player.direction == PlayerDirection::Right && newDirection == PlayerDirection::Left) ||
			(player.direction == newDirection))
		{
			return false;
		}
		player.direction = newDirection;
		return true;
	}

	void InsertSprite(Player& player, SnakeSegment& seg, CellType type)
	{
		switch (type)
		{
		case CellType::SnakeHeadUp : seg.sprite.setTexture(player.playerHeadUpTexture); break;
		case CellType::SnakeBodyHorizontal: seg.sprite.setTexture(player.playerBodyHorizontalTexture); break;
		case CellType::SnakeBodyVertical: seg.sprite.setTexture(player.playerBodyVerticalTexture); break;
		case CellType::SnakeBodyUpLeft: seg.sprite.setTexture(player.playerBodyTopLeftTexture); break;
		case CellType::SnakeBodyUpRight: seg.sprite.setTexture(player.playerBodyTopRightTexture); break;
		case CellType::SnakeBodyBottomLeft: seg.sprite.setTexture(player.playerBodyBottomLeftTexture); break;
		case CellType::SnakeBodyBottomRight: seg.sprite.setTexture(player.playerBodyBottomRightTexture); break;
		case CellType::SnakeTailUp: seg.sprite.setTexture(player.playerTailUpTexture); break;
		case CellType::SnakeHeadDown: seg.sprite.setTexture(player.playerHeadDownTexture); break;
		case CellType::SnakeHeadLeft: seg.sprite.setTexture(player.playerHeadLeftTexture); break;
		case CellType::SnakeHeadRight: seg.sprite.setTexture(player.playerHeadRightTexture); break;
		case CellType::SnakeTailDown: seg.sprite.setTexture(player.playerTailDownTexture); break;
		case CellType::SnakeTailLeft: seg.sprite.setTexture(player.playerTailLeftTexture); break;
		case CellType::SnakeTailRight: seg.sprite.setTexture(player.playerTailRightTexture); break;
		}
	}

	void DrawSnakeSegment(SnakeSegment& seg, sf::RenderWindow& window, float topPanelHeight)
	{
		seg.sprite.setPosition(static_cast<float>(seg.position.x * CELL_SIZE + CELL_SIZE / 2),
			static_cast<float>(seg.position.y * CELL_SIZE + CELL_SIZE / 2 + topPanelHeight));
		SetSpriteSize(seg.sprite, CELL_SIZE, CELL_SIZE);
		SetSpriteRelativeOrigin(seg.sprite, 0.5f, 0.5f);
		window.draw(seg.sprite);
	}


}