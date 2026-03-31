#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace SnakeGame
{
	struct AnimatedSprite
	{
		std::vector<sf::Texture> frames;
		sf::Sprite sprite;
		sf::Clock clock;
		float frameTime = 0.1f;
		size_t currentFrame = 0;
		bool isPlaying = true;
	};

	void LoadAnimatedSprite(AnimatedSprite& anim, const std::vector<std::string>& filenames);
	void UpdateAnimatedSprite(AnimatedSprite& anim);
	void DrawAnimatedSprite(AnimatedSprite& anim, sf::RenderWindow& window);

	void SetFrameTime(AnimatedSprite& anim, float newFrameTime);
	void PlayingAnimation(AnimatedSprite& anim);
	void PauseAnimation(AnimatedSprite& anim);
	void ResetAnimation(AnimatedSprite& anim);
}