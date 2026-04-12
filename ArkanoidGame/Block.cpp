#include "Block.h"
#include "Sprite.h"
#include <assert.h>
#include "Ball.h"

namespace
{
	std::string TEXTURE_ID = "Platform";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		:GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, BLOCK_WIDTH, BLOCK_HEIGHT)
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
	}

	void Block::OnHit()
	{
		hitCount = 0;
	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}
}