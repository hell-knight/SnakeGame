#include "Block.h"
#include "Sprite.h"
#include <assert.h>
#include "Ball.h"
#include "BonusManager.h"
#include "FragileBlocksBonus.h"
#include <iostream>

namespace
{
	std::string TEXTURE_ID = "Platform";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		:GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, (float)SETTINGS.BLOCK_WIDTH, (float)SETTINGS.BLOCK_HEIGHT)
	{
		sprite.setColor(color);
		std::cout << "Block created with HP: " << hitCount << std::endl;
	}

	Block::~Block()
	{
	}

	bool Block::GetCollision(std::shared_ptr<Collidable> collidableObject) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::Update(float timeDelta)
	{
		BLOCK_DAMAGE_CONTEXT.Update(timeDelta);
	}

	void Block::OnHit()
	{
		// Calculate damage based on active bonuses
		//int damage = 1;
		//if (BONUS_MANAGER.IsFragileBlocksActive())
		//{
		//	damage = hitCount; // Destroy with a single blow
		//}
		std::cout << "Block::OnHit() called! Current HP: " << hitCount << std::endl;
		int damage = BLOCK_DAMAGE_CONTEXT.GetDamage(hitCount, hitCount);
		std::cout << "Damage to apply: " << damage << std::endl;
		TakeDamage(damage);
	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}

	void Block::TakeDamage(int damage)
	{
		std::cout << "Block::TakeDamage(" << damage << ") called! HP before: " << hitCount << std::endl;
		hitCount -= damage;
		std::cout << "HP after: " << hitCount << std::endl;
		if (hitCount <= 0)
		{
			hitCount = 0;
			std::cout << "*** BLOCK DESTROYED! Spawning bonus at ("
				<< GetPosition().x << ", " << GetPosition().y << ") ***" << std::endl;
			BONUS_MANAGER.TrySpawnBonus(GetPosition());
			Emit();
			std::cout << "Block destroyed and Emit() called" << std::endl;
		}
	}

	// SmoothDestroyableBlock implementation
	void SmoothDestroyableBlock::OnHit()
	{
		std::cout << "SmoothDestroyableBlock::OnHit() called! HP: " << hitCount << std::endl;
		int damage = BLOCK_DAMAGE_CONTEXT.GetDamage(hitCount, hitCount);
		TakeDamage(damage);
	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color)
		: Block(position, color)
		, color(color)
	{
		std::cout << "SmoothDestroyableBlock created" << std::endl;
	}

	void SmoothDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<Collidable> collidableObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitCount;
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		color.a = (sf::Uint8)(255 * currentTime_ / destroyTime_);
		sprite.setColor(color);
	}

	void SmoothDestroyableBlock::TakeDamage(int damage)
	{
		std::cout << "SmoothDestroyableBlock::TakeDamage(" << damage << ") HP before: " << hitCount << std::endl;
		
		hitCount -= damage;
		std::cout << "HP after: " << hitCount << std::endl;
		if (hitCount <= 0)
		{
			hitCount = 0;
			std::cout << "*** SMOOTH BLOCK DESTROYED! Starting timer and spawning bonus ***" << std::endl;
			StartTimer(SETTINGS.BREAK_DELAY);
			BONUS_MANAGER.TrySpawnBonus(GetPosition());
			Emit();
		}
	}

	UnbreackableBlock::UnbreackableBlock(const sf::Vector2f& position)
		: Block(position, sf::Color::Color(105, 105, 105))
	{
	}

	void UnbreackableBlock::OnHit()
	{
	}

	void UnbreackableBlock::TakeDamage(int damage)
	{
	}
}