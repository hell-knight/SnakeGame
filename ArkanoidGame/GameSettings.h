#pragma once
#include <string>

namespace ArkanoidGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	const int MAX_APPLES = 80;

	// Game settings constants
	const float PLATFORM_SPEED = 300.f;
	const unsigned int PLATFORM_WIDTH = 60;
	const unsigned int PLATFORM_HEIGHT = 20;
	const unsigned int BALL_SIZE = 20;
	const unsigned int BALL_SPEED = 400;
	const float ACCELERATION = 10.f;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps
	const std::string GAME_NAME = "ArkanoidGame";
	const int GAME_POINT = 10;

	const int BLOCK_COLS = 8;
	const int BLOCK_ROWS = 3;
	const float BLOCK_SPACING = 6.f;
	const float MARGIN = 5.f;
	const float AVAIL_WIDTH = SCREEN_WIDTH - 2 * MARGIN;
	const float TOTAL_SPACING = BLOCK_SPACING * (BLOCK_COLS - 1);
	const float BLOCK_WIDTH = (AVAIL_WIDTH - TOTAL_SPACING) / BLOCK_COLS;
	const float BLOCK_HEIGHT = 30.f;
	const float BLOCK_START_X = MARGIN + (BLOCK_WIDTH + BLOCK_SPACING) / 2.f;
	const float BLOCK_START_Y = 80.f;

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some SPP
}
