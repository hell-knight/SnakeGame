#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Ball;
	class Platform;
	class block;

	enum class BonusType
	{
		None,
		FragileBlocks,
		PlatformBonus,
		FireBall
	};

	struct ActiveBonus
	{
		BonusType type;
		float remainingTime;
		float totalDuration;
	};

	class BonusManager
	{
	public:
		static BonusManager& Instance();
		void Update(float deltaTime);

		// Bonus activation
		void ActivateBonus(BonusType type, float duration = 7.0f);

		// Query active bonuses
		bool IsFragileBlocksActive() const;
		bool IsFireballActive() const;
		bool IsPlatformBonusActive() const;

		// Platform bonus modifiers
		float GetPlatformWidthMultiplier() const;
		float GetPlatformSpeedMultiplier() const;

		// Clear all bonuses (for game reset)
		void ClearAllBonuses();

		// Try to spawn bonus at position
		void TrySpawnBonus(const sf::Vector2f& position);

		// Bonus objects management
		void AddBonus(std::shared_ptr<class Bonus> bonus);
		void RemoveBonus(std::shared_ptr<class Bonus> bonus);
		const std::vector<std::shared_ptr<class Bonus>>& GetActiveBonuses() const;
		std::vector<std::shared_ptr<Bonus>>& GetActiveBonuses();

	private:
		BonusManager() = default;
		~BonusManager() = default;
		BonusManager(const BonusManager&) = delete;
		BonusManager& operator=(const BonusManager&) = delete;

		std::vector<ActiveBonus> activeBonuses;
		std::vector<std::shared_ptr<class Bonus>> bonusObjects;

		void RemoveExpiredBonuses();
	};
}
#define BONUS_MANAGER BonusManager::Instance()