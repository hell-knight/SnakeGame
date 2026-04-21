#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Collidable.h"
#include <memory>

namespace ArkanoidGame
{
	class Platform;
	// Strategy pattern for platform behavior
	class IPlatformBehavior
	{
	public:
		virtual ~IPlatformBehavior() = default;
		virtual void Update(class Platform* platform, float timeDelta) = 0;
		virtual float GetWidthMultiplier() const = 0;
		virtual float GetSpeedMultiplier() const = 0;
		virtual float CalculateReflectionAngle(float ballPosX, float platformPosX, float platformWidth) const = 0;

	};

	class DefaultPlatformBehavior : public IPlatformBehavior
	{
	public:
		virtual void Update(class Platform* platform, float timeDelta) override;
		virtual float GetWidthMultiplier() const override { return 1.5f; }
		virtual float GetSpeedMultiplier() const override { return 1.f; }
		virtual float CalculateReflectionAngle(float ballPosX, float platformPosX, float platformWidth) const override;

	};

	class BonusPlatformBehavior : public IPlatformBehavior
	{
	public:
		virtual void Update(class Platform* platform, float timeDelta) override;
		virtual float GetWidthMultiplier() const override { return 1.5f; }
		virtual float GetSpeedMultiplier() const override { return 1.3f; }
		virtual float CalculateReflectionAngle(float ballPosX, float platformPosX, float platformWidth) const override;

	};

	class Platform : public GameObject, public Collidable
	{
	public:
		Platform(const sf::Vector2f& position);

		void Update(float timeDelta) override;

		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;
		void OnHit() override {}
		bool CheckCollision(std::shared_ptr<Collidable> collidable) override;
		void restart() override;

		void SetBehavior(std::shared_ptr<IPlatformBehavior> newBehavior);
		float GetCurrentWidth() const;

		/*void SetPlatformPosition(const sf::Vector2f& pos);
		sf::Vector2f GetPlatformPosition() const;*/

		friend class IPlatformBehavior;
		friend class DefaultPlatformBehavior;
		friend class BonusPlatformBehavior;

	private:
		std::shared_ptr<IPlatformBehavior> behavior;
		/*float originalTextureWidth;
		float originalTextureHeight;*/
		void Move(float speed);
	};
}