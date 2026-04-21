#include "BonusManager.h"
#include "Bonus.h"
#include "FragileBlocksBonus.h"
#include "PlatformBonusItem.h"
#include "randomizer.h"
#include <algorithm>
#include <iostream>

namespace ArkanoidGame
{
	BonusManager& BonusManager::Instance()
	{
		static BonusManager instance;
		return instance;
	}

	void BonusManager::Update(float deltaTime)
	{
		// Update active bonuses timers
		for (auto& bonus : activeBonuses)
		{
			bonus.remainingTime -= deltaTime;
		}

		RemoveExpiredBonuses();

		// Update bonus objects
		for (auto& bonus : bonusObjects)
		{
			if (bonus)
			{
				bonus->Update(deltaTime);
			}
		}

		// Remove destroyed bonus objects
		bonusObjects.erase(
			std::remove_if(bonusObjects.begin(), bonusObjects.end(),
				[](const auto& bonus) {return !bonus || bonus->IsDestroyed(); }),
			bonusObjects.end()
		);
	}

	void BonusManager::ActivateBonus(BonusType type, float duration)
	{
		// Check if bonus already active
		auto it = std::find_if(activeBonuses.begin(), activeBonuses.end(),
			[type](const ActiveBonus& bonus) {return bonus.type == type; });

		if (it != activeBonuses.end())
		{
			// Extand duration
			it->remainingTime = std::max(it->remainingTime, duration);
			it->totalDuration = std::max(it->totalDuration, duration);
		}
		else
		{
			activeBonuses.push_back({type, duration, duration});
		}
	}

	bool BonusManager::IsFragileBlocksActive() const
	{
		return std::any_of(activeBonuses.begin(), activeBonuses.end(),
			[](const ActiveBonus& bonus) {return bonus.type == BonusType::FragileBlocks; });
	}

	bool BonusManager::IsPlatformBonusActive() const
	{
		return std::any_of(activeBonuses.begin(), activeBonuses.end(),
			[](const ActiveBonus& bonus) {return bonus.type == BonusType::PlatformBonus; });
	}

	float BonusManager::GetPlatformWidthMultiplier() const
	{
		return IsPlatformBonusActive() ? 1.5f : 1.f;
	}

	float BonusManager::GetPlatformSpeedMultiplier() const
	{
		return IsPlatformBonusActive() ? 1.3f : 1.f;
	}

	void BonusManager::ClearAllBonuses()
	{
		activeBonuses.clear();
		bonusObjects.clear();
	}

	void BonusManager::TrySpawnBonus(const sf::Vector2f& position)
	{
		// 10% chance to spawn bonus
		if (random<float>(0.0f, 100.0f) > 50.0f)
		{
			return;
		}
		
		// Random bonus type
		int bonusType = random<int>(0, 1);
		std::shared_ptr<Bonus> bonus;
		//int bonusType = 0;
		switch (bonusType)
		{
		case 0:
			bonus = std::make_shared<FragileBlocksBonus>(position);
			//std::cout << "Spawned FragileBlocksBonus at (" << position.x << ", " << position.y << ")" << std::endl;
			break;
		case 1:
			bonus = std::make_shared<PlatformBonusItem>(position);
			//std::cout << "Spawned PlatformBonusItem at (" << position.x << ", " << position.y << ")" << std::endl;
			break;
		}

		if (bonus)
		{
			bonusObjects.push_back(bonus);
			std::cout << "Total bonuses: " << bonusObjects.size() << std::endl;
		}
	}

	void BonusManager::AddBonus(std::shared_ptr<class Bonus> bonus)
	{
		if (bonus)
		{
			bonusObjects.push_back(bonus);
		}
	}

	void BonusManager::RemoveBonus(std::shared_ptr<class Bonus> bonus)
	{
		auto it = std::find(bonusObjects.begin(), bonusObjects.end(), bonus);
		if (it != bonusObjects.end())
		{
			bonusObjects.erase(it);
		}
	}

	const std::vector<std::shared_ptr<class Bonus>>& BonusManager::GetActiveBonuses() const
	{
		return bonusObjects;
	}

	std::vector<std::shared_ptr<Bonus>>& BonusManager::GetActiveBonuses()
	{
		return bonusObjects;
	}

	void BonusManager::RemoveExpiredBonuses()
	{
		activeBonuses.erase(
			std::remove_if(activeBonuses.begin(), activeBonuses.end(),
				[](const ActiveBonus& bonus) {return bonus.remainingTime <= 0.f; }),
			activeBonuses.end()
		);
	}

}