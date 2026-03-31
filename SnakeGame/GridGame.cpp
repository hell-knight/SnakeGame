#include "GridGame.h"
#include "Player.h"
#include "Apple.h"
#include "GameStatePlaying.h"

namespace SnakeGame
{
	void InitGrid(Grid& grid)
	{
		grid.cells.assign(GRID_SIZE, std::vector<CellType>(GRID_SIZE, CellType::Empty));
		
		grid.cells[GRID_SIZE / 2][GRID_SIZE / 2] = CellType::SnakeHeadRight;
		grid.cells[GRID_SIZE / 2 - 1][GRID_SIZE / 2] = CellType::SnakeBodyHorizontal;
		grid.cells[GRID_SIZE / 2 - 2][GRID_SIZE / 2] = CellType::SnakeTailLeft;

		// wall border
		for (int i = 0; i < GRID_SIZE; ++i)
		{
			grid.cells[0][i] = grid.cells[GRID_SIZE - 1][i] = CellType::Wall;
			grid.cells[i][0] = grid.cells[i][GRID_SIZE - 1] = CellType::Wall;
		}
	}

	bool IsCellFree(const Grid& grid, int cellX, int cellY)
	{
		if (cellX < 0 || cellX >= GRID_SIZE || cellY < 0 || cellY >= GRID_SIZE)
		{
			return false;
		}
		return grid.cells[cellX][cellY] == CellType::Empty;
	}

	void SetCell(Grid& grid, int cellX, int cellY, CellType type)
	{
		if (cellX >= 0 && cellX < GRID_SIZE && cellY >= 0 && cellY < GRID_SIZE)
		{
			grid.cells[cellX][cellY] = type;
		}
	}

	void SpawnApple(Grid& grid, Apple& apple)
	{
		AppleType type = AppleType::Normal;
		float rnd = static_cast<float>(rand()) / RAND_MAX;

		if (rnd < SPECIAL_APPLE_SPAWN_CHANCE)
		{
			float subRnd = static_cast<float>(rand()) / RAND_MAX;
			if (subRnd < 0.4f)
			{
				type = AppleType::Big;
			}
			else if (subRnd < 0.7f)
			{
				type = AppleType::Poisoned;
			}
			else
			{
				type = AppleType::Disorienting;
			}
		}

		apple.type = type;

		int cellX, cellY;
		do {
			cellX = rand() % GRID_SIZE;
			cellY = rand() % GRID_SIZE;
		} while (!IsCellFree(grid, cellX, cellY));
		SetCell(grid, cellX, cellY, CellType::Apple);
		apple.position = {cellX, cellY};

		apple.lifetime = (type == AppleType::Big) ? BIG_APPLE_LIFETIME : 99999.f;
	}

	Position2I SpawnStone(Grid& grid)
	{
		int cellX, cellY;
		do {
			cellX = rand() % GRID_SIZE;
			cellY = rand() % GRID_SIZE;
		} while (!IsCellFree(grid, cellX, cellY));
		SetCell(grid, cellX, cellY, CellType::Stone);
		return { cellX, cellY };
	}

	CellType ReplaceTypeCellHead(Position2I positionHead, Position2I positionBody, Position2I newPosition)
	{
		if ((newPosition.x == (positionHead.x + 1) &&
			newPosition.y == (positionBody.y - 1)) ||
			(newPosition.y == (positionHead.y + 1) &&
			newPosition.x == (positionBody.x - 1)))
		{
			return CellType::SnakeBodyBottomRight;
		}
		else if ((newPosition.x == (positionHead.x + 1) &&
			newPosition.y == (positionBody.y + 1)) ||
			(newPosition.y == (positionHead.y - 1) &&
			newPosition.x == (positionBody.x - 1)))
		{
			return CellType::SnakeBodyUpRight;
		}
		else if ((newPosition.x == (positionHead.x - 1) &&
			newPosition.y == (positionBody.y + 1)) ||
			(newPosition.y == (positionHead.y - 1) &&
			newPosition.x == (positionBody.x + 1)))
		{
			return CellType::SnakeBodyUpLeft;
		}
		else if ((newPosition.x == (positionHead.x - 1) &&
			newPosition.y == (positionBody.y - 1)) ||
			(newPosition.y == (positionHead.y + 1) &&
			newPosition.x == (positionBody.x + 1)))
		{
			return CellType::SnakeBodyBottomLeft;
		}
		else if (newPosition.y == positionBody.y)
		{
			return CellType::SnakeBodyHorizontal;
		}
		else if (newPosition.x == positionBody.x)
		{
			return CellType::SnakeBodyVertical;
		}

		return CellType::SnakeBodyHorizontal;
	}

	CellType IdentityTypeCellHead(Player& player)
	{
		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			return CellType::SnakeHeadRight;
			break;
		}
		case PlayerDirection::Up:
		{
			return CellType::SnakeHeadUp;
			break;
		}
		case PlayerDirection::Left:
		{
			return CellType::SnakeHeadLeft;
			break;
		}
		case PlayerDirection::Down:
		{
			return CellType::SnakeHeadDown;
			break;
		}
		}

		return CellType::SnakeHeadRight;
	}

	CellType IdentityTypeCellTail(Position2I positionTail, Position2I positionBody)
	{
		if (positionTail.x == (positionBody.x + 1))
		{
			return CellType::SnakeTailRight;
		}
		else if (positionTail.x == (positionBody.x - 1))
		{
			return CellType::SnakeTailLeft;
		}
		else if (positionTail.y == (positionBody.y + 1))
		{
			return CellType::SnakeTailDown;
		}
		else if (positionTail.y == (positionBody.y - 1))
		{
			return CellType::SnakeTailUp;
		}

		return CellType::SnakeTailRight;
	}

}