#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"
#include <vector>

namespace SnakeGame
{
	struct GameStatePlaying;
	struct Player;
	struct Apple;

	enum class CellType {
		Empty = 0,
		Apple = 1,
		Wall = 2,
		SnakeHeadUp = 3,
		SnakeBodyHorizontal = 4,
		SnakeBodyVertical = 5,
		SnakeBodyUpLeft = 6,
		SnakeBodyUpRight = 7,
		SnakeBodyBottomLeft = 8,
		SnakeBodyBottomRight = 9,
		SnakeTailUp = 10,
		SnakeHeadDown = 11,
		SnakeHeadLeft = 12,
		SnakeHeadRight = 13,
		SnakeTailDown = 14,
		SnakeTailLeft = 15,
		SnakeTailRight = 16,
		Stone = 17
	};

	struct Grid {
		std::vector<std::vector<CellType>> cells;
	};

	void InitGrid(Grid& grid);
	// Checks whether a cell is free
	bool IsCellFree(const Grid& grid, int cellX, int cellY);
	// Set type cell
	void SetCell(Grid& grid, int cellX, int cellY, CellType type);
	// Generait random cell for apple
	void SpawnApple(Grid& grid, Apple& apple);
	// Generait random cell for stone
	Position2I SpawnStone(Grid& grid);
	// Cell type replace head
	CellType ReplaceTypeCellHead(Position2I positionHead, Position2I positionBody, Position2I newPosition);
	// Cell type identification
	CellType IdentityTypeCellHead(Player& player);
	CellType IdentityTypeCellTail(Position2I positionTail, Position2I positionBody);
}