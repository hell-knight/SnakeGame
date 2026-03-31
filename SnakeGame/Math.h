#pragma once

namespace sf
{
	class Sprite;
}

namespace SnakeGame
{
	struct Vector2D
	{
		float x = 0.;
		float y = 0;
	};

	struct Vector2I
	{
		int x = 0;
		int y = 0;
	};

	struct Record
	{
		std::string name;
		int score;
	};

	typedef Vector2D Position2D;
	typedef Vector2I Position2I;

	Position2I GetRandomPositionInScreen(int screenWidth, int screenHeight);

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2Position, Vector2D rect2Size);

	bool IsCirclesCollide(Position2D square1Position, float circle1Radius,
		Position2D square2Position, float circle2Radius);
	
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	sf::Vector2f GetScale(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	void MyInsertionSort(std::vector<Record>& list);

	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);

	// Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min,	// Left or Top
		Middle,
		Max		// Right or Bottom
	};

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);
	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	std::string FormatNumberWithSpaces(int score);
}