#include "FireballBonusItem.h"
#include "BonusManager.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <cmath>
#include <iostream>

namespace ArkanoidGame
{
    FireballBonusItem::FireballBonusItem(const sf::Vector2f& position)
        : Bonus(position)
    {
        sprite.setColor(sf::Color::Red);
        SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
    }

    void FireballBonusItem::Activate()
    {
        BONUS_MANAGER.ActivateBonus(BonusType::FireBall, 8.0f);
    }

    void FireballBonusItem::Update(float timeDelta)
    {
        Bonus::Update(timeDelta);
        pulseTimer += timeDelta;
        float scale = 1.0f + 0.2f * std::sin(pulseTimer * 8.0f);
        sprite.setScale(scale, scale);
        sprite.rotate(180.0f * timeDelta);
    }
}