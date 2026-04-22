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
		int damage = BLOCK_DAMAGE_CONTEXT.GetDamage(hitCount, hitCount);
		TakeDamage(damage);
	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}

	void Block::TakeDamage(int damage)
	{
		hitCount -= damage;
		if (hitCount <= 0)
		{
			hitCount = 0;
			BONUS_MANAGER.TrySpawnBonus(GetPosition());
			Emit();
		}
	}

	// SmoothDestroyableBlock implementation
	void SmoothDestroyableBlock::OnHit()
	{
		int damage = BLOCK_DAMAGE_CONTEXT.GetDamage(hitCount, hitCount);
		TakeDamage(damage);
	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, const sf::Color& color)
		: Block(position, color)
		, color(color)
	{
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
		hitCount -= damage;
		if (hitCount <= 0)
		{
			hitCount = 0;
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