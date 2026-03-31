#pragma once
#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const std::string RECORDS_TABLE_FILE = "Leaderboard.txt";
	const int GRID_SIZE = 20;	// grid size N x 
	const int CELL_SIZE = 30;	// cell size in pixels
	const float TOP_PANEL_SIZE = 50.f;
	const int SCREEN_WIDTH = GRID_SIZE * CELL_SIZE;
	const int SCREEN_HEIGHT = GRID_SIZE * CELL_SIZE + static_cast<int>(TOP_PANEL_SIZE);
	const float PAUSE_TIME_START_GAME = 2.f;
	const float INITIAL_SPEED = 100.f; // Pixels per second
	const float SPEED_VERY_EASY = 50.f;
	const float SPEED_EASY = 70.f;
	const float SPEED_MIDDLE = 100.f;
	const float SPEED_HARD = 150.f;
	const float SPEED_VERY_HARD = 200.f;
	const int LEVEL_COEFFICIENT_ONE = 2;
	const int LEVEL_COEFFICIENT_TWO = 4;
	const int LEVEL_COEFFICIENT_THREE = 6;
	const int LEVEL_COEFFICIENT_FOUR = 8;
	const int LEVEL_COEFFICIENT_FIVE = 10;
	const int WITHOUT_STONE_POINT = 0;
	const int WITH_STONE_POINT = 1;
	const int SOMETIME_STONE_POINT = 2;
	const int RECORDS_POP_UP = 5;
	const int RECORDS_MAIN_MENU = 10;
	const int START_LENGHT_SNAKE = 3;
	const float PLAYER_SIZE = 20.f;
	const float ACCELERATION = 10.f; // Pixels per second
	const float APPLE_SIZE = 20.f;
	const int NUM_STONES = 5;
	const int LEADERBOARD_SIZE = 10;
	const std::string STANDART_PLAYER_NAME = "XYZ";
	const float DEATH_DELAY = 1.3f;
	const float TEMPORARY_STONE_LIFETIME = 10.f;
	const float TEMPORARY_STONE_SPAWN_CHANCE = 0.5f;
	const float BIG_APPLE_LIFETIME = 8.f;
	const int BIG_APPLE_POINT = 50;
	const float POISONED_SPEED_MULTIPLIER = 1.5f;
	const float POISONED_EFFECT_DURATION = 6.f;
	const float DISORIENT_DURATION = 5.f;
	const float SPECIAL_APPLE_SPAWN_CHANCE = 0.25f;
}