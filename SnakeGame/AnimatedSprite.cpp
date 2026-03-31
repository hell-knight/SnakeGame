#include "AnimatedSprite.h"
#include <iostream>

namespace SnakeGame
{
	void LoadAnimatedSprite(AnimatedSprite& anim, const std::vector<std::string>& filenames)
	{
		anim.frames.resize(filenames.size());

		for (size_t i = 0; i < filenames.size(); ++i)
		{
			if (!anim.frames[i].loadFromFile(filenames[i]))
			{
				std::cerr << "Erro: file no download " << filenames[i] << std::endl;
			}
		}

		if (!anim.frames.empty())
		{
			anim.sprite.setTexture(anim.frames[0]);
		}
	}

	void UpdateAnimatedSprite(AnimatedSprite& anim)
	{
		if (!anim.isPlaying || anim.frames.empty())
			return;

		if (anim.clock.getElapsedTime().asSeconds() >= anim.frameTime)
		{
			anim.currentFrame = (anim.currentFrame + 1) % anim.frames.size();
			anim.sprite.setTexture(anim.frames[anim.currentFrame]);
			anim.clock.restart();
		}
	}

	void DrawAnimatedSprite(AnimatedSprite& anim, sf::RenderWindow& window)
	{
		if (!anim.frames.empty())
		{
			window.draw(anim.sprite);
		}
	}

	void SetFrameTime(AnimatedSprite& anim, float newFrameTime)
	{
		anim.frameTime = newFrameTime;
	}

	void PlayingAnimation(AnimatedSprite& anim)
	{
		anim.isPlaying = true;
	}

	void PauseAnimation(AnimatedSprite& anim)
	{
		anim.isPlaying = false;
	}

	void ResetAnimation(AnimatedSprite& anim)
	{
		anim.currentFrame = 0;
		if (!anim.frames.empty())
			anim.sprite.setTexture(anim.frames[0]);
		anim.clock.restart();
	}


}